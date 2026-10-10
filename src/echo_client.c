#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h> //close
#include <arpa/inet.h> //inet_pton
		       //
#include <string.h> //strlen
#include <stdbool.h>
#define PORT_NUM 8080
int main(int argc, char const* argv[]) {
	(void) argc;
	(void) argv;
	int client_fd;
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	//make fd
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("client fd not initialized");
		exit(EXIT_FAILURE);
	}
	//make the address family
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT_NUM);
	//convert correct IP. May change the local ip later
	if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
		perror("failure to convert IP to socket address");
		exit(EXIT_FAILURE);
	}
	//connect
	int status;
	if ((status = connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) {
		perror("couldn't connect to server");
		exit(EXIT_FAILURE);
	}
	//char* s = "whatsupthismymessage";
	char s[100] = {0};
	while (true) {
		memset(s, 0, sizeof(s));
		//scanf("%99s", s); //SKIPS WHITESPACE?? BRUH
		if (fgets(s, sizeof(s), stdin) == NULL) {
			break;
		}

		s[strcspn(s, "\n")] = '\0';
		if (strcmp(s, "exit") == 0) {
			break;
		}
		if (strlen(s) == 0) {
			continue;
		}
		int valread;
		valread = send(client_fd, s, strlen(s), MSG_NOSIGNAL);
		if (valread < 0) {
			perror("Send failed. Try again");
			continue;
		} 

	 	char buffer[1024] = { 0 };	
		valread = recv(client_fd, buffer, 1024 - 1, 0);
		if (valread < 0) {
			perror("valread error client");
			exit(EXIT_FAILURE);
		} else if (valread == 0) {
			printf("Server shut down\n");			
			break;
		}

		printf("%s\n", buffer);
	}

	printf("Closing FD\n");
	close(client_fd);
	return 0;
}
