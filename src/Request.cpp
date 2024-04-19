#include "Request.hpp"
#include "Webserv.hpp"
#include "Response.hpp"

Request::Request(){
	
};

Request::Request(const Request &a){
	(void)a;
};

Request::Request(char *buffer, int valread) : _RequestMsg(buffer), _RequestLength(valread){
	this->ParseRequest();// should we do that here ?
};

void Request::ParseRequest(){
	
	/*this splits up the first line of the request*/
	/*and stores them in the Request class private attributes*/

	size_t PosSpace = this->_RequestMsg.find(" ");
	size_t PosTmp = 0;
	std::string MSG = this->getName();

	if (PosSpace != std::string::npos){
		this->_RequestMethod = MSG.substr(PosTmp, PosSpace);
	}

	PosTmp = PosSpace + 1;
	PosSpace = this->_RequestMsg.find(" ", PosTmp);
	if (PosSpace != std::string::npos){
		this->_RequestURL = MSG.substr(PosTmp, PosSpace - PosTmp);
	}

	PosTmp = PosSpace + 1;
	PosSpace = this->_RequestMsg.find("\n", PosTmp);
	if (PosSpace != std::string::npos){
		this->_HTTPVersion = MSG.substr(PosTmp, PosSpace - PosTmp);
	}
}

Request::~Request(){
	
};

// Request &Request::operator=(const Request &a){
// 	(void)a;
// };

std::string Request::getName()const{
	return _RequestMsg;
}

std::string Request::getMethod() const{
	return (_RequestMethod);
}

Response &Request::makeResponse(){
	Response *res = new Response();

	Response *(Response::*methods[])() = {
		&Response::GET
	};

	std::string args[1];
	args[0] = "GET";

	for (int i = 0; i < 1; i++){
		if (args[i] == this->getMethod())
			return (*(res->*methods[i])());
	}

	/*default response here*/
	return (*res);
}