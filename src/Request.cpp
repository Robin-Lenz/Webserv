#include "Request.hpp"

Request::Request(){
	
};

Request::Request(const Request &a){
	(void)a;
};

Request::Request(char *buffer, int valread) : _RequestMsg(buffer), _RequestLength(valread){
	std::cout << "Request obj cunstructed\n";
	this.ParseRequest();// should we do that here ?
};

Request::~Request(){
	
};

// Request &Request::operator=(const Request &a){
// 	(void)a;
// };

std::string Request::getName()const{
	return _RequestMsg;
}