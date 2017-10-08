#include <dbServer.h>
#include <tinyxml.h>

int main(int argc, char* argv[]) {
    khaki::EventLoop loop;
	khaki::InitLog(khaki::logger, "./dbserver.log", log4cpp::Priority::DEBUG);
    std::string filename = "../../dbserver/dbserver.xml";
    TiXmlDocument config;
    if ( !config.LoadFile(filename.c_str()) ) {
        log4cppDebug(khaki::logger, "Load config xml error");
        return 0;
    }

    TiXmlElement* root = config.RootElement();  
    TiXmlElement *mysql_host = root->FirstChildElement();
    TiXmlElement *mysql_port = mysql_host->NextSiblingElement();
	TiXmlElement *mysql_dbname = mysql_port->NextSiblingElement();
	TiXmlElement *mysql_user = mysql_dbname->NextSiblingElement();
	TiXmlElement *mysql_pwd = mysql_user->NextSiblingElement();
	TiXmlElement *listen_host = mysql_pwd->NextSiblingElement();
	TiXmlElement *listen_port = listen_host->NextSiblingElement();

    std::string mysqlHost = mysql_host->FirstChild()->Value();
    std::string mysqlPort = mysql_port->FirstChild()->Value();
	std::string mysqldbName = mysql_dbname->FirstChild()->Value();
	std::string mysqlUser = mysql_user->FirstChild()->Value();
	std::string mysqlPwd = mysql_pwd->FirstChild()->Value();
	std::string listenHost = mysql_pwd->FirstChild()->Value();
	std::string listenPort = listen_host->FirstChild()->Value();

	DbSQL* db = new DbSQL(mysqlHost, atoi(mysqlPort.c_str()), mysqldbName, mysqlUser, mysqlPwd);
	if ( !db->ConnectionDatabase() ) {
		log4cppDebug(khaki::logger, "connect mysql error");
		return 0;
	}
	
	log4cppDebug(khaki::logger, "connect mysql success");

	dbServer* g_dbServer = new dbServer(&loop, db, "127.0.0.1", 9529, 4);
	g_dbServer->start();
	loop.loop();
	//////
	delete g_dbServer;
	log4cpp::Category::shutdown();
	google::protobuf::ShutdownProtobufLibrary();
    return 0;
}