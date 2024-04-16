#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "Webserv.hpp"

class Request {
	private:
		const std::string _RequestMsg;
		int _RequestLength;
		const std::string _RequestMethod;
		const std::string _RequestURL;

	public:
		Request();
		Request(const Request &a);
		Request(char *buffer, int valraed);
		~Request();

		Request &operator=(const Request &a);

		std::string getName() const;

		

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