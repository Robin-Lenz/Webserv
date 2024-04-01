#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "Webserv.hpp"

class Request {
	private:
		const std::string _name;

	public:
		Request();
		Request(const Request &a);
		Request(int value);
		~Request();

		Request &operator=(const Request &a);

		std::string getName() const;

		// /*one function per method token */
		// GET();
		// CONNECT();
		// //
		// //
		// /*chose function to process request*/
		// complain();(like Harl)
		// 	/*list of methods allowed by a resource can be specified in an allow header field*/
		// 	/*throw exception with err code respectivly*/
};

#endif