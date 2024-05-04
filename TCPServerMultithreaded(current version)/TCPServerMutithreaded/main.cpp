#include <iostream>
#include <algorithm>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <shared_mutex>

#include "config.h"
#include "TCPServer.h"
#include "TCPClient.h"
#include "MessageBoard.h"

#define DEFAULT_PORT 12345

bool terminateServer = false;

void serverThreadFunction(TCPServer* server, ReceivedSocketData && data);


int main()
{

	TCPServer server(DEFAULT_PORT);

	ReceivedSocketData receivedData;

	std::vector<std::thread> serverThreads;

	std::cout << "Starting server. Send \"exit\" (without quotes) to terminate." << std::endl;

	while (!terminateServer)
	{
		receivedData = server.accept();
		
		if (!terminateServer)
		{
			serverThreads.emplace_back(serverThreadFunction, &server, receivedData);
		}
	}

	for (auto& th : serverThreads)
		th.join();

	std::cout << "Server terminated." << std::endl;

	return 0;
}

void serverThreadFunction(TCPServer* server, ReceivedSocketData && data)
{
	unsigned int socketIndex = (unsigned int) data.ClientSocket;
	do {
		server->receiveData(data, 0);
		

		if (data.request != "" && data.request != "EXIT")
		{

			//server->parser(Request);

			server->sendReply(data);

		//	std::cout << "[" << socketIndex << "] Bytes received: " << data.request.size() << std::endl;
			//std::cout << "[" << socketIndex << "] Data received: " << data.request << std::endl;

			/*
			start of request parser implementation used rather than provided parser using regex. 
			my solution is using string comparision
			 
			 
			
			*/

			/*
			if (Request.substr(0, 4) == "POST" || Request.substr(0, 4) == "post") {
				std::string messageEnd;
				std::string topicID;
				messageEnd = Request.find("#");
				std::cout << messageEnd;
				topicID = Request.substr();

				board.postRequest(topicID, messageEnd);

				server->sendReply(data);
				
			}

			else if (Request.substr(0, 4) == "READ" || Request.substr(0, 4) == "read") {
				std::string topicID;
				std::string postID;
				topicID = Request.find("@");
				server->sendReply(data);

			}

			else if (Request.substr(0, 4) == "LIST" || Request.substr(0, 4) == "list") {

			}

			else if (Request.substr(0, 4) == "COUNT" || Request.substr(0, 4) == "count") {

			}


			*/

			
			
			



			/*
			MessageBoard board;
			std::string Request = data.request;
			std::string messageStart;
			std::string messageEnd;
			std::string topic;

			if (Request.substr(0, 4) == "POST" || Request.substr(0, 4) == "post") {
				std::multimap<std::string, std::string> Post;

				/*
				TODO:  implement parsing for POST request. 
				
				

				


				

				server->sendReply(data);


			}

			else if (Request.substr(0, 4) == "LIST" || Request.substr(0, 4) == "list") {

				
				board.listRequest();
				
			
				server->sendReply(data);
			}

			else if (Request.substr(0, 4) == "READ" || Request.substr(0, 4) == "read") {

				
				server->sendReply(data);
			}
			else if (Request.substr(0, 4) == "COUNT" || Request.substr(0, 4) == "count") {




				server->sendReply(data);
			}

			server->sendReply(data);
			*/
		}
		else if (data.request == "exit" || data.request == "EXIT")
		{
			//std::cout << "[" << socketIndex << "] Data received: " << data.request << std::endl;
			std::cout << "[" << socketIndex << "] Exiting... Bye bye!" << std::endl;

			data.reply = data.request;
			server->sendReply(data);
		}
	} while (/*data.request != "exit" && */data.request != "EXIT" && !terminateServer);

	if (!terminateServer && /*(data.request == "exit" || */ data.request == "EXIT")
	{
		terminateServer = true;

		TCPClient tempClient(std::string("127.0.0.1"), DEFAULT_PORT);
		tempClient.OpenConnection();
		tempClient.CloseConnection();
	}

	server->closeClientSocket(data);
}
