#include <stdio.h> //perror, stdio
#include <stdlib.h> //exit()
#include <sys/socket.h> 
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> //inet_ntop
#include <unistd.h>

#include <stdbool.h>
#include <pthread.h>
#include "log.h"

#define PORT_NUM 8080

struct thread_info {
	int socket_fd;
	struct sockaddr_in sin;
};
void* handle_connection(void* args) {
	struct thread_info* p = (struct thread_info*) args;
	int new_socket = p->socket_fd;	
	struct sockaddr_in sin = p->sin;
	//socklen_t len = sizeof(sin);
	free(p);
	char presentation[16] = {0};
	unsigned int port = ntohs(sin.sin_port);
	if (inet_ntop(AF_INET, &sin.sin_addr, presentation, sizeof(presentation)) == NULL) {
		presentation[0] = '?';	
	}
	printf("Client connected. Port: %d Address: %s\n", port, presentation);
	ssize_t valread;
	char buffer[1024] = {0};	
	while (true) {
		memset(buffer, 0, sizeof(buffer));
		valread = recv(new_socket, buffer, 1024 - 1, 0); //read from client
		if (valread < 0) {
			perror("Weird error with client receiving");
			break;
		} else if (valread == 0) {
			printf("Client disconnected\n");
			break; } else {
			//buffer[valread] = '\0'; //no longer need after memcpy in loop
			if (strcmp("exit", buffer) == 0) {
				break;
			}
			char* str = "wsg ;) thanks for the message I'm currently rotting on the chan";
			valread = send(new_socket, str, strlen(str), MSG_NOSIGNAL); //send back TODO, MSG_NOSIGNAL yields error instead of SIGPIPE if fail. Helps on other clients I guess
			if (valread < 0) {
				perror("Failed to send to client");
				break;
			}

			//printf("sent %s\n", str);
			printf("[%s:%d] received: %s\n", presentation, port, buffer);
		}	
	}
	close(new_socket);
	return NULL;
}
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
	//socklen_t addrlen = sizeof(addr);
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

	while (true) {
		struct sockaddr_in sin;
		socklen_t sinlen = sizeof(sin);
		memset(&sin, 0, sinlen);
		int new_socket;
		if ((new_socket = accept(server_fd, (struct sockaddr*)&sin, &sinlen)) < 0) {
			perror("Failed to accept connection");
			continue;
		} 
		struct thread_info* t_info = malloc(sizeof(struct thread_info));
		if (t_info == NULL) {
			perror("Failed to make the malloc! Skipping client.");
			close(new_socket);
			continue;
		}
		t_info->socket_fd = new_socket;
		t_info->sin = sin;

		pthread_t t;
		int rc = pthread_create(&t, NULL, handle_connection, t_info);
		if (rc !=  0) {
			close(new_socket);
			free(t_info);	
			strerror(rc);
			continue;
		}
		pthread_detach(t); 
		//do not need to close from here, since thread will handle it.
	}
	close(server_fd);


	return 0;
	
}

