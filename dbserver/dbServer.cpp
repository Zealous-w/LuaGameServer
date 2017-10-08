#include <dbServer.h>

dbServer::dbServer(khaki::EventLoop* loop, DbSQL* dbMysql, std::string host, int port, int threadNum) :
        dbMysql_(dbMysql), server_(loop, host, port, threadNum) {
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
    sessionLists_[con->getFd()] = gameSessionPtr(new gameSession(this, con));
    log4cppDebug(khaki::logger, "dbServer fd : %d add sessionlists", con->getFd());
}

void dbServer::OnConnClose(const khaki::TcpClientPtr& con) {
    std::unique_lock<std::mutex> lck(mtx_);
    assert(sessionLists_.find(con->getFd()) != sessionLists_.end());
    sessionLists_.erase(con->getFd());
    log4cppDebug(khaki::logger, "dbServer fd : %d closed", con->getFd());
}

gameSessionPtr dbServer::GetGameSessionBySid(uint32 sid) {
    std::unique_lock<std::mutex> lck(authmtx_);
    gameSessionPtr gs;
    if ( authList_.find(sid) != authList_.end() ) {
        gs = sessionLists_[authList_[sid]];
    }
    return gs;
}

void dbServer::AddAuthGameSession(uint32 sid, uint32 sockFd) {
    std::unique_lock<std::mutex> lck(authmtx_);
    authList_.insert(std::make_pair(sid, sockFd));
    //gameSessionPtr gsp = GetGameSessionBySid(sid);
    //gdbMaster.SetGameConn(gsp);
}

void dbServer::RemoveAuthGameSession(uint32 sid) {
    std::unique_lock<std::mutex> lck(authmtx_);
    authList_.erase(sid);
}