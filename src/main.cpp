#include "Webserv.hpp"

int main(){

	struct sockaddr_in server_addr;

	/*init a socket*/
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0){
		std::cout << "Failed to create socket" << '\n';
		return (EXIT_FAILURE);
	}

	/*config socket*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	/*bind socket to port*/
	if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		std::cout << "Failed to bind socket to port" << '\n';
		return (EXIT_FAILURE);
	}

	/*listen for connection*/
	if (listen(socket_fd, 10) < 0){
		std::cout << "listen function failed" << '\n';
		return (EXIT_FAILURE);
	}
}