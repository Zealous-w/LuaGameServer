#include <dbServer.h>
#include <tinyxml.h>

int main(int argc, char* argv[]) {
    khaki::EventLoop loop;
	khaki::InitLog(khaki::logger, "./dbserver.log", log4cpp::Priority::DEBUG);
    std::string filename = "../../dbserver/dbserver.xml";
	TiXmlDocument config;
	TiXmlElement* childElement = NULL;
    if ( !config.LoadFile(filename.c_str()) ) {
        log4cppDebug(khaki::logger, "Load config xml error");
        return 0;
	}

	TiXmlElement* root = config.RootElement();
	TiXmlElement* dbElement = root->FirstChildElement("db");
	childElement = dbElement->FirstChildElement("listen_host");
	std::string listenHost = childElement->GetText();
	childElement = dbElement->FirstChildElement("listen_port");
	std::string listenPort = childElement->GetText();
	
	TiXmlElement* mysqlElement = root->FirstChildElement("mysql");
	childElement = mysqlElement->FirstChildElement("mysql_host");
	std::string mysqlHost = childElement->GetText();
	childElement = mysqlElement->FirstChildElement("mysql_port");
	std::string mysqlPort = childElement->GetText();
	childElement = mysqlElement->FirstChildElement("mysql_dbName");
	std::string mysqldbName = childElement->GetText();
	childElement = mysqlElement->FirstChildElement("mysql_user");
	std::string mysqlUser = childElement->GetText();
	childElement = mysqlElement->FirstChildElement("mysql_pwd");
	std::string mysqlPwd = childElement->GetText();

	TiXmlElement* redisElement = root->FirstChildElement("redis");
	childElement = redisElement->FirstChildElement("ip");
	std::string redisHost = childElement->GetText();
	childElement = redisElement->FirstChildElement("port");
	std::string redisPort = childElement->GetText();

	MySQLHandler* db = new MySQLHandler(mysqlHost, atoi(mysqlPort.c_str()), mysqldbName, mysqlUser, mysqlPwd);
	if ( !db->ConnectionDatabase() ) {
		log4cppDebug(khaki::logger, "connect mysql error");
		return 0;
	}
	log4cppDebug(khaki::logger, "connect mysql success, %s:%s", mysqlHost.c_str(), mysqlPort.c_str());
	
	RedisHandler* dbRedis = new RedisHandler(redisHost, atoi(redisPort.c_str()));
	if ( !dbRedis->ConnectRedis() ) {
		log4cppDebug(khaki::logger, "connect redis error");
		return 0;
	}
	log4cppDebug(khaki::logger, "connect redis success, %s:%s", redisHost.c_str(), redisPort.c_str());

	dbServer* g_dbServer = new dbServer(&loop, db, dbRedis, listenHost.c_str(), atoi(listenPort.c_str()), std::thread::hardware_concurrency());
	g_dbServer->start();
	loop.loop();
	//////
	delete g_dbServer;
	log4cpp::Category::shutdown();
	google::protobuf::ShutdownProtobufLibrary();
    return 0;
}