/*
 * Copyright (c) 2010-2017 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "image.h"

#include <framework/core/resourcemanager.h>
#include <framework/core/filestream.h>
#include <framework/graphics/apngloader.h>
#include <framework/util/qrcodegen.h>

Image::Image(const Size& size, int bpp, uint8 *pixels)
{
    m_size = size;
    m_bpp = bpp;
    m_pixels.resize(size.area() * bpp, 0);
    if(pixels)
        memcpy(&m_pixels[0], pixels, m_pixels.size());
}

ImagePtr Image::load(std::string file)
{
    ImagePtr image;
    try {
        file = g_resources.guessFilePath(file, "png");

        // load image file data
        image = loadPNG(file);
    } catch(stdext::exception& e) {
        g_logger.error(stdext::format("unable to load image '%s': %s", file, e.what()));
    }
    return image;
}

ImagePtr Image::loadPNG(const std::string& file)
{
    std::stringstream fin;
    g_resources.readFileStream(file, fin);
    ImagePtr image;
    apng_data apng;
    if(load_apng(fin, &apng) == 0) {
        image = ImagePtr(new Image(Size(apng.width, apng.height), apng.bpp, apng.pdata));
        free_apng(&apng);
    }
    return image;
}

ImagePtr Image::loadPNG(const void* data, uint32_t size)
{
    std::string temp((char*)data, size);
    std::stringstream fin(temp);
    ImagePtr image;
    apng_data apng;
    if (load_apng(fin, &apng) == 0) {
        image = ImagePtr(new Image(Size(apng.width, apng.height), apng.bpp, apng.pdata));
        free_apng(&apng);
    }
    return image;
}

void Image::savePNG(const std::string& fileName)
{
    FileStreamPtr fin = g_resources.createFile(fileName);
    if(!fin)
        stdext::throw_exception(stdext::format("failed to open file '%s' for write", fileName));

    std::stringstream data;
    save_png(data, m_size.width(), m_size.height(), 4, (unsigned char*)getPixelData());
    fin->write(data.str().c_str(), data.str().length());
    fin->flush();
    fin->close();
}

void Image::blit(const Point& dest, const ImagePtr& other)
{
    VALIDATE(m_bpp == 4);

    if (!other)
        return;

    int width = other->getWidth(), height = other->getHeight();
    uint8* otherPixels = other->getPixelData();
    for (int y = 0, p = 0; y < height; ++y) {
        int pos = ((dest.y + y) * m_size.width() + dest.x) * 4;
        for (int x = 0; x < width; ++x) {
            if (otherPixels[p + 3] != 0) {
                *(uint32_t*)&m_pixels[pos] = *(uint32_t*)&otherPixels[p];
            }
            pos += 4;
            p += 4;
        }
    }
}

void Image::paste(const ImagePtr& other)
{
    VALIDATE(m_bpp == 4);

    if (!other)
        return;

    uint8* otherPixels = other->getPixelData();
    for (int p = 0; p < other->getPixelCount(); ++p) {
        int x = p % other->getWidth();
        int y = p / other->getWidth();
        int pos = (y * m_size.width() + x) * 4;

        m_pixels[pos + 0] = otherPixels[p * 4 + 0];
        m_pixels[pos + 1] = otherPixels[p * 4 + 1];
        m_pixels[pos + 2] = otherPixels[p * 4 + 2];
        m_pixels[pos + 3] = otherPixels[p * 4 + 3];
    }
}

ImagePtr Image::upscale()
{
    VALIDATE(m_bpp == 4);

    ImagePtr newImage(new Image(m_size * 2));

    uint8* otherPixels = newImage->getPixelData();

    for (int p = 0; p < getPixelCount(); ++p) {
        int x = p % getWidth();
        int y = p / getWidth();
        int srcPos = (y * getWidth() + x) * 4;
        for (int xx = 0; xx < 2; ++xx) {
            for (int yy = 0; yy < 2; ++yy) {
                int dstPos = ((y * 2 + yy) * getWidth() * 2 + x * 2 + xx) * 4;
                for (int i = 0; i < 4; ++i) {
                    otherPixels[dstPos + i] = m_pixels[srcPos + i];
                }
            }
        }
    }

    return newImage;
}

bool Image::nextMipmap()
{
    VALIDATE(m_bpp == 4);
    VALIDATE(stdext::is_power_of_two(m_size.width()) && stdext::is_power_of_two(m_size.height()));

    int iw = m_size.width();
    int ih = m_size.height();
    if(iw == 1 && ih == 1)
        return false;

    int ow = iw > 1 ? iw/2 : 1;
    int oh = ih > 1 ? ih/2 : 1;

    std::vector<uint8> pixels(ow*oh*4, 0xFF);

    //FIXME: calculate mipmaps for 8x1, 4x1, 2x1 ...
    if(iw != 1 && ih != 1) {
        for(int x=0;x<ow;++x) {
            for(int y=0;y<oh;++y) {
                uint8 *inPixel[4];
                inPixel[0] = &m_pixels[((y*2)*iw + (x*2))*4];
                inPixel[1] = &m_pixels[((y*2)*iw + (x*2)+1)*4];
                inPixel[2] = &m_pixels[((y*2+1)*iw + (x*2))*4];
                inPixel[3] = &m_pixels[((y*2+1)*iw + (x*2)+1)*4];
                uint8 *outPixel = &pixels[(y*ow + x)*4];

                int pixelsSum[4];
                for(int i=0;i<4;++i)
                    pixelsSum[i] = 0;

                int usedPixels = 0;
                for(int j=0;j<4;++j) {
                    // ignore colors of complete alpha pixels
                    if(inPixel[j][3] < 16)
                        continue;

                    for(int i=0;i<4;++i)
                        pixelsSum[i] += inPixel[j][i];

                    usedPixels++;
                }

                // try to guess the alpha pixel more accurately
                for(int i=0;i<4;++i) {
                    if(usedPixels > 0)
                        outPixel[i] = pixelsSum[i] / usedPixels;
                    else
                        outPixel[i] = 0;
                }
                outPixel[3] = pixelsSum[3]/4;
            }
        }
    }

    m_pixels = pixels;
    m_size = Size(ow, oh);
    return true;
}

void Image::flipVertically()
{
    uint rowIncrement = m_size.height() * m_bpp;
    uint8* pixelData = m_pixels.data();

    for(int y = 0; y < (getHeight() / 2); ++y) {
        uint8* itr1 = &pixelData[y * rowIncrement];
        uint8* itr2 = &pixelData[(m_size.height() - y - 1) * rowIncrement];

        for(std::size_t x = 0; x < rowIncrement; ++x) {
            std::swap(*(itr1 + x), *(itr2 + x));
        }
    }
}

void Image::reverseChannels()
{
    uint8* pixelData = m_pixels.data();
    for(uint8* itr = pixelData; itr < pixelData + m_pixels.size(); itr += m_bpp) {
        std::swap(*(itr + 0), *(itr + 2));
    }
}

/*
 *

void Texture::generateSoftwareMipmaps(std::vector<uint8> inPixels)
{
    bind();

    VALIDATE(stdext::is_power_of_two(m_glSize.width()) && stdext::is_power_of_two(m_glSize.height()));

    Size inSize = m_glSize;
    Size outSize = inSize / 2;
    std::vector<uint8> outPixels;

    int mipmap = 1;
    while(true) {
        outPixels.resize(outSize.area()*4, 0);

        // this is a simple bilinear filtering algorithm, it combines every 4 pixels in one pixel
        for(int x=0;x<outSize.width();++x) {
            for(int y=0;y<outSize.height();++y) {
                uint8 *inPixel[4];
                inPixel[0] = &inPixels[((y*2)*inSize.width() + (x*2))*4];
                inPixel[1] = &inPixels[((y*2)*inSize.width() + (x*2)+1)*4];
                inPixel[2] = &inPixels[((y*2+1)*inSize.width() + (x*2))*4];
                inPixel[3] = &inPixels[((y*2+1)*inSize.width() + (x*2)+1)*4];
                uint8 *outPixel = &outPixels[(y*outSize.width() + x)*4];

                int pixelsSum[4];
                for(int i=0;i<4;++i)
                    pixelsSum[i] = 0;

                int usedPixels = 0;
                for(int j=0;j<4;++j) {
                    // ignore colors of complete alpha pixels
                    if(inPixel[j][3] < 16)
                        continue;

                    for(int i=0;i<4;++i)
                        pixelsSum[i] += inPixel[j][i];

                    usedPixels++;
                }

                // try to guess the alpha pixel more accurately
                for(int i=0;i<4;++i) {
                    if(usedPixels > 0)
                        outPixel[i] = pixelsSum[i] / usedPixels;
                    else
                        outPixel[i] = 0;
                }
                outPixel[3] = pixelsSum[3]/4;
            }
        }

        glTexImage2D(GL_TEXTURE_2D, mipmap++, GL_RGBA, outSize.width(), outSize.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &outPixels[0]);

        if(inSize.width() == 1 || inSize.height() == 1)
            break;

        inPixels = std::move(outPixels);
        inSize /= 2;
        outSize /= 2;
    }

    if(!m_hasMipmaps) {
        m_hasMipmaps = true;
        setupFilters();
    }
}
*/

ImagePtr Image::fromQRCode(const std::string& code, int border)
{
    enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_HIGH;  // Error correction level

    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(code.c_str(), tempBuffer, qrcode, errCorLvl, qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if (!ok)
        return nullptr;
    int size = qrcodegen_getSize(qrcode);
    ImagePtr image(new Image(Size(size + border * 2, size + border * 2)));
    for (int x = 0; x < size + border * 2; ++x) {
        for (int y = 0; y < size + border * 2; ++y) {
            image->setPixel(x, y, qrcodegen_getModule(qrcode, x - border, y - border) ? Color::black : Color::white);
        }
    }
    return image;
}
