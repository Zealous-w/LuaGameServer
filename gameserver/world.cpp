#include <unistd.h>
#include <world.h>
#include <Log.h>
#include <protocol/out/cs.pb.h>
#include <protocol/in/base.pb.h>
#include <base/error.h>
#include <sys/prctl.h>

World::World():running_(false), thread_(&World::Run, this) {
    RegisterCmd();
    timerQueue_.AddTimer(1, 2, std::bind(&World::ShowOnlineNumber, this));
}

World::~World() {
    thread_.join();
}

void World::Run() {
    {
        std::unique_lock<std::mutex> lck(mtx_);
        cond_.wait(lck, [this]()->bool{ return running_; });
    }
    ::prctl(PR_SET_NAME, "World");
    while ( running_ ) {
        loop_.getPoll()->poll(100);
        MsgProcess(msgQueue_);
        MsgProcess(dbMsgQueue_);
        struct timeval tm;
        gettimeofday(&tm, NULL);
        schedule_.update(tm);
        timerQueue_.update(tm);
    }
}

void World::MsgProcess(khaki::queue<struct PACKET>& msg) {
    if ( msg.size() > 0 ) {
        std::queue<struct PACKET> tmpQueue = msg.popAll();
        while ( !tmpQueue.empty() ) {
            struct PACKET pkt = tmpQueue.front();
            DispatcherCmd(pkt);
            tmpQueue.pop();
        }
    }
}

void World::ShowOnlineNumber() {
    log4cppDebug(khaki::logger, "Online Numer : %d", users_.size());
}

void World::SendToGateway(uint32 msgId, uint64 uid, uint32 sid, std::string& msg) {
    gSession_->SendPacket(msgId, uid, sid, msg);
}
 
void World::SendToDb(uint32 msgId, uint64 uid, uint32 sid, std::string& msg) {
    dSession_->SendPacket(msgId, uid, sid, msg);
}

void World::RegisterCmd() {
    /////////GS///////////
    REGISTER_CMD_CALLBACK(gs::ProtoID::ID_G2S_Login, HandlerLogin);
    REGISTER_CMD_CALLBACK(gs::ProtoID::ID_G2S_Create, HandlerCreate);
    REGISTER_CMD_CALLBACK(gs::ProtoID::ID_G2S_LoginOffline, HandlerOffline);
    //REGISTER_CMD_CALLBACK(cs::ProtoID::ID_C2S_GetMoney, HandlerGetMoney);
    ///////////RS///////////
    REGISTER_CMD_CALLBACK(sr::ProtoID::ID_R2S_Login, HandlerRSLogin);
    REGISTER_CMD_CALLBACK(sr::ProtoID::ID_R2S_Create, HandlerRSCreate);
}

void World::DispatcherCmd(struct PACKET& msg) {
    if ( command_.find(msg.cmd) != command_.end() ) {
        command_[msg.cmd](msg);
    } else {
        log4cppDebug(khaki::logger, "LUA proto : %d", msg.cmd);
        auto player = GetPlayer(msg.uid);
        if (player == NULL) {
            log4cppDebug(khaki::logger, "Not Found user : %d", msg.uid);
            return;
        }

        lua_getglobal(L, LUA_HANDLER_CMD_DISPATCHER);
        tolua_pushusertype(L, (void*)player, "Player");
        tolua_pushusertype(L, &msg, "PACKET");
        
		if (lua_pcall(L, 2, 0, 0) != 0) {
            log4cppDebug(khaki::logger, "LUA lua_pcall dispatcherCmd Error : %d %s", msg.cmd, lua_tostring(L, -1));
			return;
        }
        log4cppDebug(khaki::logger, "PLAYER : level:%d, money:%d", player->level, player->money);
        lua_pop(L,-1);
    }
}

void World::AddPlayer(Player* player) {
    bool ret = users_.insert(std::make_pair(player->uid, player)).first->second;
    //log4cppDebug(khaki::logger, "AddPlayer : %lld, ret:%d", player->uid, ret);
}

void World::RemovePlayer(uint64 uid) {
    auto player = users_.find(uid);
    if (player != users_.end()) {
        Player* p = player->second;
        users_.erase(uid);
        delete p;
    }
}

Player* World::GetPlayer(uint64 uid) {
    auto player = users_.find(uid);
    if (player != users_.end()) {
        return player->second;
    }
    return NULL;
}

///////////GS///////////
bool World::HandlerLogin(struct PACKET& pkt) {
    gs::G2S_Login recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }

    uint64 uid = recv.uid();

    sr::S2R_Login msg;
    uint32 msgId = uint32(sr::ProtoID::ID_S2R_Login);
    msg.set_tokenid(recv.tokenid());
    msg.set_uid(uid);
    std::string msgStr = msg.SerializeAsString();
    dSession_->SendPacket(msgId, pkt.uid, pkt.sid, msgStr);
    //log4cppDebug(khaki::logger, "HandlerLogin proto : %d %d", pkt.cmd, uid);
}

bool World::HandlerCreate(struct PACKET& pkt) {
    gs::G2S_Create recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }

    uint64 uid = recv.uid();

    sr::S2R_Create msg;
    uint32 msgId = uint32(sr::ProtoID::ID_S2R_Create);
    msg.set_tokenid(recv.tokenid());
    base::User* user = msg.mutable_user();
    ///////////////// create new role
    user->set_uid(pkt.uid);
    user->set_sid(pkt.sid);
    user->set_name("wkw");
    user->set_level(1);
    user->set_money(100);
    ////////////////
    std::string msgStr = msg.SerializeAsString();
    dSession_->SendPacket(msgId, user->uid(), pkt.sid, msgStr);
    //log4cppDebug(khaki::logger, "HandlerCreate proto : %d %d", pkt.cmd, uid);
}

bool World::HandlerOffline(struct PACKET& pkt) {
    gs::G2S_LoginOffline recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    uint64 uid = recv.uid();
    RemovePlayer(uid);
    //log4cppDebug(khaki::logger, "HandlerOffline uid : %d", uid);
    return true;
}

bool World::HandlerGetMoney(struct PACKET& pkt) {
    cs::C2S_GetMoney recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    uint32 addMoney = recv.addmoney();
    auto player = GetPlayer(pkt.uid);
    if (player == NULL) {
        log4cppDebug(khaki::logger, "Not Found user : %d", pkt.uid);
        return false;
    }

    cs::S2C_GetMoney cmsg;
    uint32 cMsgId = uint32(cs::ProtoID::ID_S2C_GetMoney);
    cmsg.set_ret(1); //1:ok
    cmsg.set_summoney(0);
    if (addMoney > 10000) {
        log4cppDebug(khaki::logger, "Limit Money : %d", addMoney);
        cmsg.set_ret(2);//ERROR
        std::string msgStr = cmsg.SerializeAsString();
        gSession_->SendPacket(cMsgId, pkt.uid, pkt.sid, msgStr);
        return false;
    }
    player->money += addMoney;
    cmsg.set_summoney(player->money);
    std::string cmsgStr = cmsg.SerializeAsString();
    gSession_->SendPacket(cMsgId, pkt.uid, pkt.sid, cmsgStr);

    sr::S2R_SaveUser msg;
    uint32 msgId = uint32(sr::ProtoID::ID_S2R_SaveUser);
    msg.set_allocated_user(player->SaveUser());
    std::string msgStr = msg.SerializeAsString();
    dSession_->SendPacket(msgId, pkt.uid, pkt.sid, msgStr);
    log4cppDebug(khaki::logger, "HandlerGetMoney proto : %d %d", pkt.cmd, pkt.uid);
    return true;
}

bool World::HandlerAddItem(struct PACKET& pkt) {
    auto player = GetPlayer(pkt.uid);
    if (player == NULL) {
        log4cppDebug(khaki::logger, "Not Found user : %d", pkt.uid);
        return false;
    }
    //ItemSystem::GetSystem().AddItem(player, 0, 0);
    return true;
}

///////////RS///////////
bool World::HandlerRSLogin(struct PACKET& pkt) {
    sr::R2S_Login recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    uint32 ret = recv.ret();
    base::User bUser = recv.user();
    if (ret == ERROR_LOGIN_SUCCESS) {
        Player* user = new Player();
        user->uid = bUser.uid();
        user->sid = bUser.sid();
        user->name = bUser.name();
        user->level = bUser.level();
        user->money = bUser.money();
        AddPlayer(user);
    }
    
    ///////////////////
    gs::S2G_Login msg;
    uint32 msgId = uint32(gs::ProtoID::ID_S2G_Login);
    msg.set_tokenid(recv.tokenid());
    msg.set_ret(ret);
    std::string msgStr = msg.SerializeAsString();
    gSession_->SendPacket(msgId, pkt.uid, pkt.sid, msgStr);
    //log4cppDebug(khaki::logger, "HandlerRSLogin proto : %d %d %d %d", pkt.cmd, pkt.uid, ret, bUser.uid());
    return true;
}

bool World::HandlerRSCreate(struct PACKET& pkt) {
    sr::R2S_Create recv;
    if ( !recv.ParseFromString(pkt.msg) )
    {
        log4cppDebug(khaki::logger, "proto parse error : %d", pkt.cmd);
        return false;
    }
    uint32 ret = recv.ret();

    ///////////////////
    gs::S2G_Create msg;
    uint32 msgId = uint32(gs::ProtoID::ID_S2G_Create);
    msg.set_tokenid(recv.tokenid());
    msg.set_ret(ret);
    std::string msgStr = msg.SerializeAsString();
    gSession_->SendPacket(msgId, pkt.uid, pkt.sid, msgStr);
    //log4cppDebug(khaki::logger, "HandlerRSCreate proto : %d %d ret=%d", pkt.cmd, pkt.uid, ret);
    return true;
}