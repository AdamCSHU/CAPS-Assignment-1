/*

#ifndef __MESSAGEBOARD_H
#define __MESSAGEBOARD_H

#include <map>
#include <string>
#include <vector>
#include <shared_mutex>


class MessageBoard
{

public:
	MessageBoard();
	~MessageBoard();
	std::string readRequest(std::string topicID, int postID);
	int postRequest(std::string topicID, std::string message);
	int countRequest(std::string topicID);
	std::string listRequest();
	void exit();

private:
	std::shared_mutex lock;
	std::map<std::string, std::vector<std::string>> topicandmessages;
	std::vector<std::string> topics();
	static std::string trun(std::string message, int length);

};

#endif // __MESSAGEBOARD_H
*/