#ifndef REDIS_HANDLER_H
#define REDIS_HANDLER_H
#include <hiredis/hiredis.h>
#include <string>

class RedisHandler {
public:
    RedisHandler(std::string& host, uint32_t port);
    ~RedisHandler();

    bool ConnectRedis();

    //command
    int Del(const char* key);
    int Set(const char* key, const char* value);
private:
    std::string host_;
    uint32_t port_;
    redisContext* redisCtx;
};

#endif