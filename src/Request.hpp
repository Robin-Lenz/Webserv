#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "Webserv.hpp"
#include "Response.hpp"

class Response;

class Request {
	
	private:
		const std::string _RequestMsg;
		void ParseRequest();
	
	protected:
		int _RequestLength;
		std::string _RequestMethod;
		std::string _RequestURL;
		std::string _HTTPVersion;

	public:
		Request();
		Request(const Request &a);
		Request(char *buffer, int valraed);
		~Request();

		Request &operator=(const Request &a);

		std::string getName() const;
		std::string getMethod() const;

		Response &makeResponse();
};

#endif