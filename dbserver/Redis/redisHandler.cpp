#include "redisHandler.h"
#include <Log.h>

RedisHandler::RedisHandler(std::string& host, uint32_t port) : 
    host_(host), port_(port) {

}

RedisHandler::~RedisHandler() {

}

bool RedisHandler::ConnectRedis() {
    redisCtx = ::redisConnect(host_.c_str(), port_);
    if(redisCtx != NULL && redisCtx->err)
    {
        log4cppError(khaki::logger, "redis connect error: %s\n", redisCtx->errstr);
        return false;
    }
    return true;
}

int RedisHandler::Del(const char* key) {

}

int RedisHandler::Set(const char* key, const char* value) {

}