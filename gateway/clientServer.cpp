#include <clientServer.h>

clientServer::clientServer(khaki::EventLoop* loop, std::string host, int port, int threadNum) :
        server_(loop, host, port, threadNum), markId_(0) {
    server_.setConnectionCallback(std::bind(&clientServer::OnConnection, 
                        this, std::placeholders::_1));
    server_.setConnCloseCallback(std::bind(&clientServer::OnConnClose,
                        this, std::placeholders::_1));
    loop->getTimer()->AddTimer(std::bind(&clientServer::ShowOnlineNumber, this), khaki::util::getTime(), 10);
}

clientServer::~clientServer() {

}

void clientServer::start() {
    server_.start();
}

void clientServer::ShowOnlineNumber() {
    std::unique_lock<std::mutex> lck(mtx_);
    log4cppDebug(khaki::logger, "Gateway Online Numer : %d", sessionLists_.size());
}

void clientServer::OnConnection(const khaki::TcpClientPtr& con) {
    std::unique_lock<std::mutex> lck(mtx_);
    if (sessionLists_.find(con->getUniqueId()) != sessionLists_.end()) {
        log4cppError(khaki::logger, "clientServer OnConnection ERROR : %lld add sessionlists size:%d", con->getUniqueId(), sessionLists_.size());
        return;
    }
    sessionLists_[con->getUniqueId()] = clientSessionPtr(new clientSession(this, con));
    //log4cppDebug(khaki::logger, "clientServer getIpPort : %lld add sessionlists size:%d", con->getIpPort(), sessionLists_.size());
}
void clientServer::OnConnClose(const khaki::TcpClientPtr& con) {
    std::unique_lock<std::mutex> lck(mtx_);
    uint64 uniqueId = con->getUniqueId();
    auto client = sessionLists_.find(uniqueId);
    if (client != sessionLists_.end()) {
        client->second->UserOffline();
        sessionLists_.erase(client);
        //log4cppDebug(khaki::logger, "clientSession fd : %d closed", con->getFd());
    } else {
        log4cppError(khaki::logger, "clientSession OnConnClose Error getUniqueId : %lld", uniqueId);
    }
}

clientSessionPtr clientServer::GetClientSessionByUniqueId(uint64 uniqueId) {
    std::unique_lock<std::mutex> lck(mtx_);
    clientSessionPtr csp;
    if ( sessionLists_.find(uniqueId) != sessionLists_.end() ) {
        csp = sessionLists_[uniqueId];
    } else {
        log4cppDebug(khaki::logger, "GetClientSessionByUniqueId uniqueId : %lld not exit", uniqueId);
    }
    return csp;
}