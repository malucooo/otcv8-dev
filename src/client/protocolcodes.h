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

#ifndef PROTOCOLCODES_H
#define PROTOCOLCODES_H

#include "global.h"

namespace Proto {
    enum LoginServerOpts {
        LoginServerError = 10,
        LoginServerMotd = 20,
        LoginServerUpdateNeeded = 30,
        LoginServerCharacterList = 100
    };

    enum ItemOpcode {
        StaticText = 96,
        UnknownCreature = 97,
        OutdatedCreature = 98,
        Creature = 99
    };

    enum GameServerOpcodes : uint8
    {
        GameServerLoginOrPendingState = 10,
        GameServerGMActions = 11,
        GameServerEnterGame = 15,
        GameServerUpdateNeeded = 17,
        GameServerLoginError = 20,
        GameServerLoginAdvice = 21,
        GameServerLoginWait = 22,
        GameServerLoginSuccess = 23,
        GameServerSessionEnd = 24,
        GameServerStoreButtonIndicators = 25, // 1097
        GameServerPingBack = 29,
        GameServerPing = 30,
        GameServerChallenge = 31,
        GameServerDeath = 40,
        GameServerSupplyStash = 41,
        GameServerSpecialContainer = 42,
        GameServerPartyAnalyzer = 43,

        // all in game opcodes must be greater than 50
        GameServerFirstGameOpcode = 50,
        // otclient ONLY
        GameServerExtendedOpcode = 50,
        // NOTE: add any custom opcodes in this range
        // 51 - 99
        GameServerChangeMapAwareRange = 51,

        // original tibia ONLY
        GameServerSendClientCheck = 99,
        GameServerFullMap = 100,
        GameServerMapTopRow = 101,
        GameServerMapRightRow = 102,
        GameServerMapBottomRow = 103,
        GameServerMapLeftRow = 104,
        GameServerUpdateTile = 105,
        GameServerCreateOnMap = 106,
        GameServerChangeOnMap = 107,
        GameServerDeleteOnMap = 108,
        GameServerMoveCreature = 109,
        GameServerOpenContainer = 110,
        GameServerCloseContainer = 111,
        GameServerCreateContainer = 112,
        GameServerChangeInContainer = 113,
        GameServerDeleteInContainer = 114,
        GameServerSetInventory = 120,
        GameServerDeleteInventory = 121,
        GameServerOpenNpcTrade = 122,
        GameServerPlayerGoods = 123,
        GameServerCloseNpcTrade = 124,
        GameServerOwnTrade = 125,
        GameServerCounterTrade = 126,
        GameServerCloseTrade = 127,
        GameServerAmbient = 130,
        GameServerGraphicalEffect = 131,
        GameServerTextEffect = 132,
        GameServerMissleEffect = 133,
        GameServerItemClasses = 134,
        GameServerTrappers = 135,
        GameServerCreatureHealth = 140,
        GameServerCreatureLight = 141,
        GameServerCreatureOutfit = 142,
        GameServerCreatureSpeed = 143,
        GameServerCreatureSkull = 144,
        GameServerCreatureParty = 145,
        GameServerCreatureUnpass = 146,
        GameServerCreatureMarks = 147,
        GameServerPlayerHelpers = 148,
        GameServerCreatureType = 149,
        GameServerEditText = 150,
        GameServerEditList = 151,
        GameServerSendGameNews = 152,
        GameServerSendBlessDialog = 155,
        GameServerBlessings = 156,
        GameServerPreset = 157,
        GameServerPremiumTrigger = 158, // 1038
        GameServerPlayerDataBasic = 159, // 950
        GameServerPlayerData = 160,
        GameServerPlayerSkills = 161,
        GameServerPlayerState = 162,
        GameServerClearTarget = 163,
        GameServerPlayerModes = 167,
        GameServerSpellDelay = 164, // 870
        GameServerSpellGroupDelay = 165, // 870
        GameServerMultiUseDelay = 166, // 870
        GameServerSetStoreDeepLink = 168, // 1097
        GameServerSendRestingAreaState = 169,
        GameServerTalk = 170,
        GameServerChannels = 171,
        GameServerOpenChannel = 172,
        GameServerOpenPrivateChannel = 173,
        GameServerRuleViolationChannel = 174,
        GameServerRuleViolationRemove = 175,
        GameServerRuleViolationCancel = 176,
        GameServerRuleViolationLock = 177,
        GameServerOpenOwnChannel = 178,
        GameServerCloseChannel = 179,
        GameServerTextMessage = 180,
        GameServerCancelWalk = 181,
        GameServerWalkWait = 182,
        GameServerUnjustifiedStats = 183,
        GameServerPvpSituations = 184,
        GameServerRefreshBestiaryTracker = 185,
        GameServerTaskHuntingBasicData = 186,
        GameServerTaskHuntingData = 187,
        GameServerFloorChangeUp = 190,
        GameServerFloorChangeDown = 191,
        GameServerLootContainers = 192,
        GameServerChooseOutfit = 200,
        GameServerSendUpdateImpactTracker = 204,
        GameServerSendItemsPrice = 205,
        GameServerSendUpdateSupplyTracker = 206,
        GameServerSendUpdateLootTracker = 207,
        GameServerKillTracker = 209, // 1281
        GameServerVipAdd = 210,
        GameServerVipState = 211,
        GameServerVipLogout = 212,
        GameServerSendBestiaryEntryChanged = 217,
        GameServerTutorialHint = 220,
        GameServerAutomapFlag = 221,
        GameServerSendDailyRewardCollectionState = 222,
        GameServerCoinBalance = 223, // 1080
        GameServerStoreError = 224, // 1080
        GameServerRequestPurchaseData = 225, // 1080
        GameServerSendOpenRewardWall = 226,
        GameServerSendDailyReward = 228,
        GameServerSendRewardHistory = 229,
        GameServerSendPreyTimeLeft = 231,
        GameServerSendPreyData = 232,
        GameServerSendPreyRerollPrice = 233,
        GameServerSendShowDescription = 234,
        GameServerSendImbuementWindow = 235,
        GameServerSendCloseImbuementWindow = 236,
        GameServerSendError = 237,
        GameServerResourceBalance = 238, // 1281
        GameServerWorldTime = 239, // 1281
        GameServerQuestLog = 240,
        GameServerQuestLine = 241,
        GameServerCoinBalanceUpdating = 242, // 1080
        GameServerChannelEvent = 243, // 910
        GameServerItemInfo = 244, // 910
        GameServerPlayerInventory = 245, // 910
        GameServerMarketEnter = 246, // 944
        GameServerMarketLeave = 247, // 944
        GameServerMarketDetail = 248, // 944
        GameServerMarketBrowse = 249, // 944
        GameServerModalDialog = 250, // 960
        GameServerStore = 251, // 1080
        GameServerStoreOffers = 252, // 1080
        GameServerStoreTransactionHistory = 253, // 1080
        GameServerStoreCompletePurchase = 254  // 1080
    };

    enum ItemOpcode {
        StaticText = 96,
        UnknownCreature = 97,
        OutdatedCreature = 98,
        Creature = 99
    };

    enum GameServerOpcodes : uint8
    };

    enum ClientOpcodes : uint8
    {
        ClientEnterAccount = 0x1,
        ClientPendingGame = 0xA,
        ClientEnterGame = 0x0F,
        ClientLeaveGame = 0x14,
        ClientPing = 0x1D,
        ClientPingBack = 0x1E,

        // all in game opcodes must be equal or greater than 50
        ClientFirstGameOpcode = 0x32,

        // otclient ONLY
        ClientExtendedOpcode = 0x32,
        ClientChangeMapAwareRange = 0x33,

        // NOTE: add any custom opcodes in this range
        // 51 - 99

        // original tibia ONLY
        ClientAutoWalk = 0x64,
        ClientWalkNorth = 0x65,
        ClientWalkEast = 0x66,
        ClientWalkSouth = 0x67,
        ClientWalkWest = 0x68,
        ClientStop = 0x69,
        ClientWalkNorthEast = 0x6A,
        ClientWalkSouthEast = 0x6B,
        ClientWalkSouthWest = 0x6C,
        ClientWalkNorthWest = 0x6D,
        ClientTurnNorth = 0x6F,
        ClientTurnEast = 0x70,
        ClientTurnSouth = 0x71,
        ClientTurnWest = 0x72,
        ClientEquipItem = 0x77, // 910
        ClientMove = 0x78,
        ClientInspectNpcTrade = 0x79,
        ClientBuyItem = 0x7A,
        ClientSellItem = 0x7B,
        ClientCloseNpcTrade = 0x7C,
        ClientRequestTrade = 0x7D,
        ClientInspectTrade = 0x7E,
        ClientAcceptTrade = 0x7F,
        ClientRejectTrade = 0x80,
        ClientUseItem = 0x82,
        ClientUseItemWith = 0x83,
        ClientUseOnCreature = 0x84,
        ClientRotateItem = 0x85,
        ClientCloseContainer = 0x87,
        ClientUpContainer = 0x88,
        ClientEditText = 0x89,
        ClientEditList = 0x8A,
        ClientLook = 0x8C,
        ClientLookCreature = 0x8D,
        ClientTalk = 0x96,
        ClientRequestChannels = 0x97,
        ClientJoinChannel = 0x98,
        ClientLeaveChannel = 0x99,
        ClientOpenPrivateChannel = 0x9A,
        ClientOpenRuleViolation = 0x9B,
        ClientCloseRuleViolation = 0x9C,
        ClientCancelRuleViolation = 0x9D,
        ClientCloseNpcChannel = 0x9E,
        ClientChangeFightModes = 0xA0,
        ClientAttack = 0xA1,
        ClientFollow = 0xA2,
        ClientInviteToParty = 0xA3,
        ClientJoinParty = 0xA4,
        ClientRevokeInvitation = 0xA5,
        ClientPassLeadership = 0xA6,
        ClientLeaveParty = 0xA7,
        ClientShareExperience = 0xA8,
        ClientDisbandParty = 0xA9,
        ClientOpenOwnChannel = 0xAA,
        ClientInviteToOwnChannel = 0xAB,
        ClientExcludeFromOwnChannel = 0xAC,
        ClientCancelAttackAndFollow = 0xBE,
        ClientUpdateTile = 0xC9,
        ClientRefreshContainer = 0xCA,
        ClientBrowseField = 0xCB,
        ClientSeekInContainer = 0xCC,
        ClientRequestOutfit = 0xD2,
        ClientChangeOutfit = 0xD3,
        ClientMount = 0xD4, // 870
        ClientAddVip = 0xDC,
        ClientRemoveVip = 0xDD,
        ClientEditVip = 0xDE,
        ClientBugReport = 0xE6,
        ClientRuleViolation = 0xE7,
        ClientDebugReport = 0xE8,
        ClientTransferCoins = 0xEF, // 1080
        ClientRequestQuestLog = 0xF0,
        ClientRequestQuestLine = 0xF1,
        ClientNewRuleViolation = 0xF2, // 910
        ClientRequestItemInfo = 0xF3, // 910
        ClientMarketLeave = 0xF4, // 944
        ClientMarketBrowse = 0xF5, // 944
        ClientMarketCreate = 0xF6, // 944
        ClientMarketCancel = 0xF7, // 944
        ClientMarketAccept = 0xF8, // 944
        ClientAnswerModalDialog = 0xF9, // 960
        ClientOpenStore = 0xFA, // 1080
        ClientRequestStoreOffers = 0xFB, // 1080
        ClientBuyStoreOffer = 0xFC, // 1080
        ClientOpenTransactionHistory = 0xFD, // 1080
        ClientRequestTransactionHistory = 0xFE  // 1080
    };

    enum CreatureType_t : uint8_t {
        CREATURETYPE_PLAYER = 0,
        CREATURETYPE_MONSTER = 1,
        CREATURETYPE_NPC = 2,
        CREATURETYPE_SUMMONPLAYER = 3,
        CREATURETYPE_SUMMON_OWN = 3,
        CREATURETYPE_SUMMON_OTHERS = 4,
        CREATURETYPE_HIDDEN = 5,
        CREATURE_TYPE_UNKNOW = 0xFF
    };

    enum CreaturesIdRange {
        PlayerStartId = 0x10000000,
        PlayerEndId = 0x40000000,
        MonsterStartId = 0x40000000,
        MonsterEndId = 0x80000000,
        NpcStartId = 0x80000000,
        NpcEndId = 0xffffffff
    };

    void buildMessageModesMap(int version);
    Otc::MessageMode translateMessageModeFromServer(uint8 mode);
    uint8 translateMessageModeToServer(Otc::MessageMode mode);
}

#endif
