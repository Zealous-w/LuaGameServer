#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H
#include <base/basic.h>

DEFINE_CLASS(GameConfig)
public:
    void setServerId(uint32_t sid) {serverId_ = sid;}
    uint32_t getServerId() {return serverId_;}
private:
    std::string serverName_;
    uint32_t serverId_;
DEFINE_CLASS_END
#define gConfig GameConfig::GetSystem()
#endif