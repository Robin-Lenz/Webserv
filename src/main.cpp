#include "Webserv.hpp"
#include "Response.hpp"
#include "Request.hpp"

#include <sys/ioctl.h>


int main(){

	struct sockaddr_in server_addr;
	long valread;
	int rc = 0;// to catch returnvalues for err managament
	struct pollfd fds[200];
	char buffer[30000] = {0};// should we keep this size or is there a reason why we should chose a specific size

	/*flags*/
	int close_con = 0;
	int server_alive = 1;
	int arr_reloaded = 0;
	(void)arr_reloaded;

	int on = 1;// get rid of it

	int nfds = 1;


	/*init a socket*/
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0){
		std::cout << "Failed to create socket" << '\n';
		return (EXIT_FAILURE);
	}


	/*allow socket descriptor to be reuseable*/		//made no noticeable difference so far
	rc = setsockopt(socket_fd, SOL_SOCKET,  SO_REUSEADDR,(char *)&on, sizeof(on));
	if (rc < 0)
	{
	  perror("setsockopt() failed");
	  close(socket_fd);
	  exit(-1);
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

	/*makes socket non-blocking*/
	rc = ioctl(socket_fd, FIONBIO, (char *)&on);// function allowed ?
	if (rc < 0)
	{
		perror("ioctl() failed");
		close(socket_fd);
		exit(-1);
	}

	/* Initialize the pollfd structure*/
	memset(fds, 0 , sizeof(fds));// allowed function ?

	fds[0].fd = socket_fd;
	fds[0].events = POLLIN;

	int tmp_socket = 0;
	socklen_t address_len;
	address_len = sizeof(sockaddr_in);

	while (server_alive)
	{
		// std::cout << "waiting for poll()\n";
		rc = poll(fds, nfds, 10000);
		if (rc < 0){
			std::cout << "poll() failed\n";
			continue ;
		}
		if (rc == 0){
			std::cout << "poll() timed out\n";
			continue ;
		}

		/* for-loop to find fds ready to read from*/
		for (int i = 0; i < nfds; i++){
			if (fds[i].revents == 0){
				continue;
			}

			/*Client sent envet but not POLLIN - should we break here + err msg*/
			if (fds[i].revents != POLLIN){
				continue;
			}

			if (fds[i].fd == socket_fd){
				// std::cout << "listening socket is readable\n";

				/*accept all pending connections and add to polll structure*/
				while (tmp_socket != -1)
				{
					std::cout << " before accept "<< '\n';
					if ((tmp_socket = accept(socket_fd, (struct sockaddr*)&server_addr, &address_len)) < 0 ){
						std::cout << "accept() failed " << tmp_socket << '\n';
						break;
					}
					printf(" New incoming connection %d\n", tmp_socket);
					fds[nfds].fd = tmp_socket;
					fds[nfds].events = POLLIN;
					nfds++;
				}
				tmp_socket = 0;
			}
			else{
				/*keep on receiving until recv() fails*/
				valread = recv(fds[i].fd, buffer, sizeof(buffer), 0);
				if (valread < 0){//(valread = recv(fds[i].fd, buffer, sizeof(buffer), 0)) < 0){
					std::cout << "recv function failed" << '\n';
					close_con = 1;
					break ;
				}

				/*was connection closed by client ?*/
				if (valread == 0){
					close_con = 1;
					break;
				}

				while (1)
				{

					Request Req(buffer, valread);
					Response &Res = Req.makeResponse();


					std::cout << Res.getResponse().c_str() << '\n';
					std::cout << Res.getResLen() << '\n';
					valread = send(fds[i].fd, Res.getResponse().c_str(), Res.getResLen(), 0);
					if (valread < 0){//send(fds[i].fd, Res.getResponse().c_str(), Res.getResLen(), 0) < 0){
						std::cout << "send() failed\n";
						close_con = 1;
						break;
					}
					// write(fds[i].fd, "\n", 2); // to flush

					std::cout << " message has been sent " << '\n';
					break;
				}

				if (close_con){
					close(fds[i].fd);
					fds[i].fd = -1;
					arr_reloaded = 1;
				}
				write(fds[i].fd, "\n", 2);
			break;// this break is just for debug reasons
			}

		/*close all fds that are -1*/
		if (arr_reloaded)
		{
			arr_reloaded = 0;
			for (int i = 0; i < nfds; i++){
				if (fds[i].fd == -1){
					std::cout << "fd to eliminate " << fds[i].fd << '\n';
					for (int j = i; j < nfds; j++){
						fds[j].fd = fds[j+1].fd;
					}
				}
				nfds--;
				i--;
			}
		}
	}
}
	return 0;
}