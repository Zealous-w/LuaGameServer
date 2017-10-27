#include <dbServer.h>

dbServer::dbServer(khaki::EventLoop* loop, MySQLHandler* dbMysql, RedisHandler* dbRedis, std::string host, int port, int threadNum) :
        dbMysql_(dbMysql), dbRedis_(dbRedis), server_(loop, host, port, threadNum) {
    server_.setConnectionCallback(std::bind(&dbServer::OnConnection, 
                        this, std::placeholders::_1));
    server_.setConnCloseCallback(std::bind(&dbServer::OnConnClose,
                        this, std::placeholders::_1));
}

dbServer::~dbServer() {
    if (dbMysql_ != NULL) delete dbMysql_;
}

void dbServer::start() {
    server_.start();
}

void dbServer::OnConnection(const khaki::TcpClientPtr& con) {
    std::unique_lock<std::mutex> lck(mtx_);
    sessionLists_[con->getUniqueId()] = gameSessionPtr(new gameSession(this, con));
    log4cppDebug(khaki::logger, "dbServer fd : %d add sessionlists", con->getUniqueId());
}

void dbServer::OnConnClose(const khaki::TcpClientPtr& con) {
    std::unique_lock<std::mutex> lck(mtx_);
    assert(sessionLists_.find(con->getUniqueId()) != sessionLists_.end());
    uint32 sid = sessionLists_[con->getUniqueId()]->GetSid();
    sessionLists_.erase(con->getUniqueId());
    authList_.erase(sid);
    log4cppDebug(khaki::logger, "dbServer fd : %d closed", sid);
}

gameSessionPtr dbServer::GetGameSessionBySid(uint32 sid) {
    std::unique_lock<std::mutex> lck(mtx_);
    gameSessionPtr gs;
    if ( authList_.find(sid) != authList_.end() ) {
        gs = sessionLists_[authList_[sid]];
    } else {
        log4cppDebug(khaki::logger, "GetGameSessionBySid sid : %d not exit", sid);
    }
    return gs;
}

void dbServer::AddAuthGameSession(uint32 sid, uint64 uniqueId) {
    std::unique_lock<std::mutex> lck(mtx_);
    authList_.insert(std::make_pair(sid, uniqueId));
}

void dbServer::RemoveAuthGameSession(uint32 sid) {
    std::unique_lock<std::mutex> lck(mtx_);
    authList_.erase(sid);
}