#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "Webserv.hpp"
// #include "Response.hpp"

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
		// Response &makeResponse(const Request &req);
		// Response &GET(Request &req);

		// /*one function per method token */
		// GET — Fetch a URL
    	// HEAD — Fetch information about a URL
    	// PUT — Store to an URL
    	// POST — Send form data to a URL and get a response back
    	// DELETE — Delete a URL GET and POST (forms) are commonly used
		// //
		// //
		// /*chose function to process request*/
		// complain();(like Harl)
		// 	/*list of methods allowed by a resource can be specified in an allow header field*/
		// 	/*throw exception with err code respectivly*/
};

#endif