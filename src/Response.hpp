#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "Webserv.hpp"
#include "Request.hpp"

class Request;

class Response {
	private:
		std::string _Response;
		int _ResLen;

	public:
		Response();
		// Response(const Response &a);
		// Response();
		~Response();

		Response &operator=(const Response &a);

		std::string getResponse() const;
		int getResLen()const;
		
		Response *makeResponse(Request &req);
		Response *GET(Request &req);
};

#endif