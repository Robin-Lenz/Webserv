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

Response *Response::makeResponse(Request &req){
	Response *res = new Response();

	Response *(Response::*methods[])(Request &req) = {
		&Response::GET
	};

	std::string args[1];
	args[0] = "GET";

	for (int i = 0; i < 1; i++){
		if (args[i] == req.getMethod())
			return (this->*methods[i](&req));

	}
	
	
	/*default response here*/
	return (res);
}

Response *Response::GET(Request &req){
	(void)req;

	/*check for client permission to access data here*/
	
	_Response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\n";
	_ResLen = _Response.length();
	std::cout << "GET called\n" << _Response << '\n';
	return (this);
}