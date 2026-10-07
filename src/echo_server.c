#include <stdio.h> //perror, stdio
#include <stdlib.h> //exit()
#include <sys/socket.h> 
#include <netinet/in.h>
#include <string.h>
//#include <arpa/inet.h>
#include <unistd.h>

#include <stdbool.h>

#define PORT_NUM 8080

int main(int argc, char* argv[]) {
	(void) argc; //warnings
	(void) argv;
	int server_fd;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket() failed");
		exit(EXIT_FAILURE);		
	} //create socket

	int opt = 1; //for SO_REUSEADDR
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		perror("setsockopt REUSEADDR");
		exit(EXIT_FAILURE);
	} //SO_REUSEADDR makes it so that the socket (which stays active after closing program) can be rebinded to immediately
	
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT_NUM);
	//now bind
	if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	int MAX_QUEUE = 5;
	if (listen(server_fd, MAX_QUEUE) < 0) {
		perror("LISTEN");
		exit(EXIT_FAILURE);
	}	
	bool flag = true;
	while (flag) {	
		int new_socket;
		if ((new_socket = accept(server_fd, (struct sockaddr*)&addr, &addrlen)) < 0) {
			perror("ACCEPT");
			exit(EXIT_FAILURE);	
		} 
		ssize_t valread;
		char buffer[1024] = {0};	
		while (true) {
			memset(buffer, 0, sizeof(buffer));
			valread = recv(new_socket, buffer, 1024 - 1, 0); //read from client
			if (valread < 0) {
				perror("valread");
				close(new_socket);
				exit(EXIT_FAILURE);
			} else if (valread == 0) {
				printf("Client disconnected");
				break;
			} else {
				//buffer[valread] = '\0'; //no longer need after memcpy in loop
				printf("%s\n", buffer); //print it out
				if (strcmp("exit_all_connections", buffer) == 0) { // TODO remove ts
					flag = false;
				} else if (strcmp("exit", buffer) == 0) {
					break;
				}
				char* str = "wsg ;)";
				send(new_socket, str, strlen(str), 0); //send back
				printf("sent %s", buffer);
			}	
		}
		close(new_socket);
	}
	close(server_fd);


	return 0;
	
}
