#ifndef PLAYER_H
#define PLAYER_H
#include <base/basic.h>
#include <protocol/in/base.pb.h>

#define DEFINE_PARAM(func, type, var) \
private:\
    type var;\
public:\
    void Set##func(type tmp) {\
        var = tmp;\
    }\
    type Get##func() {\
        return var;\
    }

class Player {
public:
    Player();
    ~Player();
    base::User* SaveUser();
    void Desc();

    uint64_t GetUid() const ;
    void SetUid(uint64_t tuid);
    std::string GetName() const ;
    void SetName(std::string tname);
    uint32_t GetSid() const ;
    void SetSid(uint32_t tsid);
    uint32_t GetLevel() const ;
    void SetLevel(uint32_t tlevel);
    uint64_t GetMoney() const ;
    void SetMoney(uint64_t tmoney);
    
public:
    uint64_t uid;
    uint32_t sid;
    ////base info////
    std::string name;
    uint32_t level;
    uint64_t money;
};
#endif