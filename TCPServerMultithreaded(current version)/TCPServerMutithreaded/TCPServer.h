#ifndef __TCPSERVER_H
#define __TCPSERVER_H
//written b adam campbell

#include <vector>
#include <map>
#include "ReceivedSocketData.h"
#include <shared_mutex>


class TCPServer
{
public:
	TCPServer(unsigned short int port);
	~TCPServer();
	ReceivedSocketData accept();
	void receiveData(ReceivedSocketData& ret, bool blocking);
	int sendReply(ReceivedSocketData reply);
	std::string TCPServer::parseRequests(std::string request);
	void test(std::string topicID, std::string message);

	void OpenListenSocket();
	void CloseListenSocket();
	int closeClientSocket(ReceivedSocketData &reply);

private:
	SOCKET ListenSocket;
	unsigned short int port;
	std::string portString;
	std::vector<std::string> topics();
	static std::string trun(std::string message, int length);
	std::map<std::string, std::vector<std::string>> topicandmessages;
};

#endif __TCPSERVER_H
