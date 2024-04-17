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

		// /*one function per method token */
		// GET — Fetch a URL
    	// HEAD — Fetch information about a URL
    	// PUT — Store to an URL
    	// POST — Send form data to a URL and get a response back
    	// DELETE — Delete a URL GET and POST (forms) are commonly used
};

#endif