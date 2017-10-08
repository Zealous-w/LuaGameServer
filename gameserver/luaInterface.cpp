#include "luaInterface.h"
#include <Log.h>
#include <world.h>

void logInfo(const char* str) {
    log4cppInfo(khaki::logger, "%s", str);
}

void sendToDb(uint32 msgId, uint64 uid, uint32 sid, std::string& msg) {
    gWorld.SendToDb(msgId, uid, sid, msg);
}

void SendToGateway(uint32 msgId, uint64 uid, uint32 sid, std::string& msg) {
    gWorld.SendToGateway(msgId, uid, sid, msg);
}
   