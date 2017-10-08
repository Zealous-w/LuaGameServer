#ifndef PLAYER_H
#define PLAYER_H
#include <base/basic.h>
#include <protocol/in/base.pb.h>

class Player {
public:
    Player();
    ~Player();
    base::User* SaveUser();
public:
    uint64 uid;
    uint32 sid;
    ////base info////
    std::string name;
    uint32 level;
    uint64 money;
};
#endif