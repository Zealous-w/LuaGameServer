#include <unistd.h>
#include <world.h>
#include <Log.h>
#include <protocol/out/cs.pb.h>
#include <protocol/in/base.pb.h>
#include <base/error.h>

World::World():thread_(&World::Run, this) {
    running_ = false;
    RegisterCmd();
    timerM_.AddTimer(std::bind(&World::ShowOnlineNumber, this), khaki::util::getTime(), 10);
}

World::~World() {
    thread_.join();
}

void World::Run() {
    while ( running_ ) {
        MsgProcess(msgQueue_);
        MsgProcess(dbMsgQueue_);
        timerM_.Run(khaki::util::getTime());
        usleep(10000);
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

void World::RegisterCmd() {
    ///////////GS///////////
    // REGISTER_CMD_CALLBACK(gs::ProtoID::ID_G2S_Login, HandlerLogin);
    // REGISTER_CMD_CALLBACK(gs::ProtoID::ID_G2S_Create, HandlerCreate);
    // REGISTER_CMD_CALLBACK(gs::ProtoID::ID_G2S_LoginOffline, HandlerOffline);
    // REGISTER_CMD_CALLBACK(cs::ProtoID::ID_C2S_GetMoney, HandlerGetMoney);
    // ///////////RS///////////
    // REGISTER_CMD_CALLBACK(sr::ProtoID::ID_R2S_Login, HandlerRSLogin);
    // REGISTER_CMD_CALLBACK(sr::ProtoID::ID_R2S_Create, HandlerRSCreate);
}

void World::DispatcherCmd(struct PACKET& msg) {
    if ( command_.find(msg.cmd) != command_.end() ) {
        command_[msg.cmd](msg);
    } else {
        lua_getglobal(L, "dispatcherCmd");

        lua_newtable(L);
        lua_pushstring(L, "len");
        lua_pushnumber(L, msg.len);
        lua_settable(L,-3);

        lua_pushstring(L, "cmd");
        lua_pushnumber(L, msg.cmd);
        lua_settable(L,-3);

        lua_pushstring(L, "uid");
        lua_pushnumber(L, msg.uid);
        lua_settable(L,-3);

        lua_pushstring(L, "sid");
        lua_pushnumber(L, msg.sid);
        lua_settable(L,-3);

        lua_pushstring(L, "msg");
        lua_pushstring(L, msg.msg.c_str());
        lua_settable(L,-3);

		if (lua_pcall(L, 2, 1, 0) != 0) {
			return;
		}
        lua_pop(L,-1);
        log4cppDebug(khaki::logger, "error proto : %d", msg.cmd);
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