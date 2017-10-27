#include "luaInterface.h"
#include <Log.h>
#include <world.h>

void logInfo(const char* str) {
    log4cppInfo(khaki::logger, "%s", str);
}

void SendToDb(uint32 msgId, uint64 uid, uint32 sid, std::string& msg) {
    gWorld.SendToDb(msgId, uid, sid, msg);
}

void SendToGateway(uint32 msgId, uint64 uid, uint32 sid, std::string& msg) {
    gWorld.SendToGateway(msgId, uid, sid, msg);
}

uint32 GetTime() {
    return khaki::util::getTime();
}

uint64 AddTimer(uint32 timeout, uint32 iv, int handler) {
    //log4cppInfo(khaki::logger, "timeout:%d, iv:%d, handler:%d", timeout, iv, handler);
    gWorld.GetScheduler().AddTimer(timeout, iv, handler);
}