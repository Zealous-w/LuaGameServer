#include <gameServer.h>

gameServer::gameServer(khaki::EventLoop* loop, std::string host, int port, int threadNum) :
        server_(loop, host, port, threadNum) {
    server_.setConnectionCallback(std::bind(&gameServer::OnConnection, 
                        this, std::placeholders::_1));
    server_.setConnCloseCallback(std::bind(&gameServer::OnConnClose, 
                        this, std::placeholders::_1));
}

gameServer::~gameServer(){}

void gameServer::start() {
    server_.start();
}

void gameServer::OnConnection(const khaki::TcpClientPtr& con) {
    std::unique_lock<std::mutex> lck(mtx_);
    sessionLists_[con->getUniqueId()] = gameSessionPtr(new gameSession(this, con));
    log4cppDebug(khaki::logger, "gameServer fd : %d add sessionlists", con->getUniqueId());
}
void gameServer::OnConnClose(const khaki::TcpClientPtr& con) {
    std::unique_lock<std::mutex> lck(mtx_);
    assert(sessionLists_.find(con->getUniqueId()) != sessionLists_.end());
    uint32 sid = sessionLists_[con->getUniqueId()]->GetSid();
    sessionLists_.erase(con->getUniqueId());
    authList_.erase(sid);
    log4cppDebug(khaki::logger, "gametSession fd : %d closed", sid);
}

gameSessionPtr gameServer::GetGameSessionBySid(uint32 sid) {
    std::unique_lock<std::mutex> lck(mtx_);
    gameSessionPtr gs;
    if ( authList_.find(sid) != authList_.end() ) {
        gs = sessionLists_[authList_[sid]];
    } else {
        log4cppDebug(khaki::logger, "GetGameSessionBySid sid : %d not exit", sid);
    }
    return gs;
}

void gameServer::AddAuthGameSession(uint32 sid, uint64 uniqueId) {
    std::unique_lock<std::mutex> lck(mtx_);
    authList_.insert(std::make_pair(sid, uniqueId));
}

void gameServer::RemoveAuthGameSession(uint32 sid) {
    std::unique_lock<std::mutex> lck(mtx_);
    authList_.erase(sid);
}