#ifndef __TCPSERVER_H
#define __TCPSERVER_H
//written b adam campbell
#include "MessageBoard.h"
#include "ReceivedSocketData.h"

class TCPServer
{
public:
	TCPServer(unsigned short int port);
	~TCPServer();
	ReceivedSocketData accept();
	void receiveData(ReceivedSocketData& ret, bool blocking);
	int sendReply(ReceivedSocketData reply);
	std::string parseRequests(std::string request);

	void OpenListenSocket();
	void CloseListenSocket();
	int closeClientSocket(ReceivedSocketData &reply);

private:
	SOCKET ListenSocket;
	unsigned short int port;
	std::string portString;
	MessageBoard board;
};

#endif __TCPSERVER_H
