#include "MessageBoard.h"

std::vector<std::string> MessageBoard::topics()
{
	std::vector<std::string> topickeys;
	lock.lock_shared();
	for (auto topic : this->topicandmessages) {
		topickeys.push_back(topic.first);
	}

	lock.unlock_shared();
	return topickeys;
}

//truncate function, checks message length against maxlength (140) and uses substring method to adjust string accordingly.
inline std::string MessageBoard::trun(std::string message, int length)
{

	//int maxLength = 140;
	//if (message.length() > maxLength) {
	//	return message = message.substr(0, maxLength);
	//}
	
	unsigned int newLength = message.length() > length ? length : message.length();
	return message.substr(0, newLength);
	
}

MessageBoard::MessageBoard()
{
}

MessageBoard::~MessageBoard()
{
}

std::string MessageBoard::listRequest()
{

	std::string messageList = "";
	std::vector<std::string> topicVector = topics();

	if (topicVector.size() < 1) {
		return messageList;
	}

	for (auto it : topicVector) {
		messageList += it + "#";
	}

	messageList.pop_back();
	return messageList;

}

int MessageBoard::countRequest(std::string topicID) {

	lock.lock_shared();
	unsigned int messageCount = this->topicandmessages[topicID].size();
	lock.unlock_shared();
	return messageCount;
}

int MessageBoard::postRequest(std::string topicID, std::string message) {

	std::string topicAdjust = trun(topicID, 140);
	std::string messageAdjust = trun(message, 140);
	lock.lock();

	int messageID = this->topicandmessages[topicAdjust].size();
	this->topicandmessages[topicAdjust].push_back(messageAdjust);
	lock.unlock();
	return messageID;
}

std::string MessageBoard::readRequest(std::string topicID, int postID) {
	std::string topicAdjust = trun(topicID, 140);
	lock.lock_shared();
	bool valid = this->topicandmessages.count(topicAdjust) && this->topicandmessages[topicAdjust].size() > postID;

	if (!valid) {
		lock.unlock_shared();
		return "";
	}

	std::string msg = this->topicandmessages[topicAdjust][postID];
	lock.unlock_shared();
	return msg;
}

void MessageBoard::exit() {
	return;
}