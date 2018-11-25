#include <nan.h>
#include "log.h"
#include "main.h"

RakClientInterface *pRakClient = NULL;
bool IsConnectionRequired = true;

int iAreWeConnected = 0, iConnectionRequested = 0, iSpawned = 0, iGameInited = 0, iSpawnsAvailable = 0;
int iReconnectTime = 2 * 1000, iNotificationDisplayedBeforeSpawn = 0;
PLAYERID g_myPlayerID;
char g_szNickName[32];
struct stPlayerInfo playerInfo[MAX_PLAYERS];
struct stVehiclePool vehiclePool[MAX_VEHICLES];

bool chatListening = false;

/** Callbacks **/
v8::Local<v8::Function> listenChatFunc;


char* ToCString(const v8::String::Utf8Value& value) {
    return *value ? *value : "<string conversion failed>";
}

void ConnectAsync() {
    int connectionId = 0;
    srand((unsigned int)GetTickCount());
    pRakClient = RakNetworkFactory::GetRakClientInterface();
    if (pRakClient == NULL)
        return;

    pRakClient->SetMTUSize(576);
    RegisterRPCs(pRakClient);
    int iLastStatsUpdate = GetTickCount();
    int iLastMoney = iMoney;
    int iLastDrunkLevel = iDrunkLevel;
    while(1) {
        UpdateNetwork(pRakClient);
        if (IsConnectionRequired) {
            Log("Connecting to %s", settings.server.szAddr);

            // pRakClient->SetPassword(password);
            connectionId = (int) pRakClient->Connect(settings.server.szAddr, settings.server.iPort, 0, 0, 5);
            Log(connectionId > 0 ? "Connected" : "Connection failed");

            IsConnectionRequired = false;
        }
    }
}

void Connect(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    int setLoaded = LoadSettings();
    Log("Settings Loaded %i", setLoaded);

    listenChatFunc = v8::Local<v8::Function>::Cast(info[0]);

    strcpy(g_szNickName, settings.server.szNickname);

    ConnectAsync();
    // std::thread t1(ConnectAsync);

    // t1.join();
    // v8::Local<v8::Value> nodeConnectionId = Nan::New(connectionId);
    // info.GetReturnValue().Set(nodeConnectionId);
}


void MessageReceived(char* message) {
    const int argc = 1;
    v8::Local<v8::Value> args[argc];
    args[0] = Nan::New(message).ToLocalChecked();
    Nan::Callback cb(listenChatFunc);
    cb.Call(argc, args);
}

void Init(v8::Local<v8::Object> exports) {
    exports->Set(Nan::New("connect").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(Connect)->GetFunction());
}


NODE_MODULE(NODE_GYP_MODULE_NAME, Init);