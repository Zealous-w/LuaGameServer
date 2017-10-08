#ifndef DBSQL_H
#define DBSQL_H 
#include <mysql++/mysql++.h>
#include <base/basic.h>
#include <protocol/in/base.pb.h>

class DbSQL {
public:
    typedef std::vector<std::vector<std::string>> VQueryResult;
    DbSQL(std::string host, uint16_t port, std::string dbName, std::string user, std::string pwd);
    ~DbSQL();
public:
    bool ConnectionDatabase();
    bool CreateDbDatabase(std::string& dbName);
    bool CreateDbTable(std::string& dbTable);
    mysqlpp::StoreQueryResult GetData(std::string& sql);
    void CloseMysql();
    ////////////////////////
    bool CreateGameTable();

    ////////////////////////
    bool LoadUser(base::User* user, uint64 uid);
    ////////////////////////

    ////////RESULT/////////
    bool GetUserBaseInfo(base::User* user, uint64 uid);
    bool NewUserBaseInfo(base::User& user);
    bool SaveUserBaseInfo(base::User& user);
private:
    std::string host_; 
    uint16_t port_; 
    std::string dbName_; 
    std::string user_; 
    std::string pwd_;
    mysqlpp::Connection db_;
    mysqlpp::Query query_;
};

#endif