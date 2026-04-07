#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
	int create_socket, cont;
	int buffsize = 1024;
	char *buffer = malloc(buffsize);
	char fname[256];
	struct sockaddr_in address;

	if((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0)
		printf("The socket is created\n");

	address.sin_family = AF_INET;
	address.sin_port = htons(15001);
	inet_pton(AF_INET, argv[1], &address.sin_addr);

	if((connect(create_socket, (struct sockaddr*)&address, sizeof(address))) == 0)
		printf("The connection was accepted\n");

	printf("Enter the file name:\n");
	scanf("%s", &fname);
	send(create_socket, fname, 256, 0);

	while((cont = recv(create_socket, buffer, buffsize, 0)) > 0){
		write(1, buffer, cont);
	}
	return close(create_socket);
}