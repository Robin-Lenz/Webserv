#include "Response.hpp"
#include "Webserv.hpp"
#include "Request.hpp"

Response::Response(){
	
};

// Response::Response(const Response &a){
// 	(void)a;
// };

// Response::Response(){
	
// };

Response::~Response(){
	delete this;
};

// Response &Response::operator=(const Response &a){
// 	(void)a;
// 	return a;
// };

std::string Response::getResponse()const {
	return (_Response);
}

int Response::getResLen()const{
	return (_ResLen);
}

Response *Response::GET(){

	/*check for client permission to access data here*/

	// _Response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 8\n\nhallo";
	_Response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nHello, world!";

	_ResLen = _Response.length();
	std::cout << "GET called\n" << _Response << '\n';
	return (this);
}