#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <nan.h>


#pragma comment(lib, "ws2_32")
// raknet stuff
#include "../PacketEnumerations.h"
#include "../RakNetworkFactory.h"
#include "../RakClientInterface.h"
#include "../NetworkTypes.h"
#include "../BitStream.h"
#include "../StringCompressor.h"
#include "../SAMP/samp_netencr.h"

#include "../tinyxml/tinyxml.h"

enum eRunModes
{
    RUNMODE_RCON,
    RUNMODE_BARE,
    RUNMODE_STILL,
    RUNMODE_NORMAL,
    RUNMODE_FOLLOWPLAYER,
    RUNMODE_FOLLOWPLAYERSVEHICLE,
    RUNMODE_PLAYROUTES
};

#include "../SAMP/SAMPRPC.h"
#include "../common/common.h"
#include "../net/netrpc.h"
#include "../net/netgame.h"
#include "localplayer.h"
#include "misc_funcs.h"
#include "xmlsets.h"
#include "log.h"

#pragma warning(disable:4996)

struct stVehiclePool
{
    int iDoesExist;
    float fPos[3];
    int iModelID;
};

extern int iAreWeConnected, iConnectionRequested, iSpawned, iGameInited, iSpawnsAvailable;
extern int iReconnectTime;
extern PLAYERID g_myPlayerID;
extern char g_szNickName[32];

extern int iMoney, iDrunkLevel, iLocalPlayerSkin;
extern struct stPlayerInfo playerInfo[MAX_PLAYERS];
extern struct stVehiclePool vehiclePool[MAX_VEHICLES];

extern PLAYERID imitateID;

void handleQueries(char *s, int len);
void SaveTextDrawData ( WORD wTextID, TEXT_DRAW_TRANSMIT *pData, CHAR* cText );
void gen_random(char *s, const int len);
void MessageReceived(char* message);
extern RakClientInterface *pRakClient;
