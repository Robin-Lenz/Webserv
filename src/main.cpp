#include "Webserv.hpp"

int main(){

	struct sockaddr_in server_addr;
	long valread;
	(void)valread;
	char hello[] = "Hello from server";

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
	/*listen(socked_fd, max_int_pending_con)*/
	if (listen(socket_fd, 10) < 0){
		std::cout << "listen function failed" << '\n';
		return (EXIT_FAILURE);
	}

	int tmp_socket;
	socklen_t *address_len = (socklen_t *)calloc(sizeof(socklen_t), 1);// are we allowed to use calloc ?
	
	while (1)
	{
		std::cout << "waiting to accept connection\n";
		if ((tmp_socket = accept(socket_fd, (struct sockaddr*)&server_addr, address_len)) < 0 ){
			std::cout << "accept function failed" << '\n';
			return (EXIT_FAILURE);
		}

		char buffer[30000] = {0};
		valread = read(tmp_socket, buffer, 30000);

		std::cout << buffer << '\n';

		write(tmp_socket, hello, std::strlen(hello));

		std::cout << " message has been sent " << '\n';

		close(tmp_socket);
	}
	return 0;
}