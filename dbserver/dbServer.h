#ifndef GAME_CLIENT_SERVER_H
#define GAME_CLIENT_SERVER_H
#include <khaki.h>
#include <Queue.h>
#include <unordered_map>
#include <gameSession.h>
#include <base/common.h>
#include <MySQL/mysqlHandler.h>
#include <Redis/redisHandler.h>

#include <map>
#include <functional>

class dbServer {
public: 
    dbServer(khaki::EventLoop* loop, MySQLHandler* dbMysql, RedisHandler* dbRedis, std::string host, int port, int threadNum);
    ~dbServer();

    void start();

    void OnConnection(const khaki::TcpClientPtr& con);
	void OnConnClose(const khaki::TcpClientPtr& con);
    gameSessionPtr GetGameSessionBySid(uint32 sid);
    void AddAuthGameSession(uint32 sid, uint64 uniqueId);
    void RemoveAuthGameSession(uint32 sid);

    MySQLHandler* GetDb() { return dbMysql_; }
    RedisHandler* GetRedis() { return dbRedis_; }
private:
    MySQLHandler* dbMysql_;
    RedisHandler* dbRedis_;
    khaki::TcpThreadServer server_;
	std::mutex mtx_;
	std::unordered_map<uint32/*sid*/, gameSessionPtr> sessionLists_;
    std::map<uint32/*sid*/, uint64/*fd*/> authList_;
    khaki::queue<struct PACKET> queue_;
};

#endif