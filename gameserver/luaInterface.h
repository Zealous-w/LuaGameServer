#ifndef LUA_INTERFACE_H
#define LUA_INTERFACE_H
#include <base/basic.h>
#include <stdio.h>
#include <string>
#include <functional>

void logInfo(const char* str);

//net
void SendToDb(uint32 msgId, uint64 uid, uint32 sid, std::string& msg);
void SendToGateway(uint32 msgId, uint64 uid, uint32 sid, std::string& msg);

uint32 GetTime();
uint64 AddTimer(uint32 timeout, uint32 iv, int handler);
#endif