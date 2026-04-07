#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<arpa/inet.h>

// socket
// bind
// listen
// accept

int main(){
	int cont, create_socket, new_socket, addrlen, fd;
	int buffsize = 1024;
	char *buffer = malloc(buffsize);
	char fname[256];
	struct sockaddr_in address;

	if((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0)
		printf("The socket was created\n");

	address.sin_family = AF_INET;
	address.sin_port = htons(15001);
	address.sin_addr.s_addr = INADDR_ANY;

	if(bind(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0)
		printf("Binding Successfull\n");

	listen(create_socket, 3);
	addrlen = sizeof(struct sockaddr);

	if((new_socket = accept(create_socket, (struct sockaddr*)&address, &addrlen))>0)
		printf("The client is connected %d", inet_ntoa(address.sin_addr));

	recv(new_socket, fname, 256, 0);

	if((fd = open(fname, O_RDONLY)) < 0){
		printf("Error while opening file\n");
		exit(0);
	}

	while((cont = read(fd, buffer, buffsize)) > 0){
		printf("%s\n", buffer);
		send(new_socket, buffer, cont, 0);
	}

	close(new_socket);

	return close(create_socket);
}