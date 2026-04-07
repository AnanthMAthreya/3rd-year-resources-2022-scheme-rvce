#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>


void str_echo(int sockfd, struct sockaddr *cli_address, int clilen)
{
    int n;
    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    int addrlen;
    for (;;)
    {
        addrlen = clilen;
        n = recvfrom(sockfd, buffer, bufsize, 0, cli_address, &addrlen); //RECV BUFFER
        sendto(sockfd, buffer, n, 0, cli_address, addrlen);
    } //sendto
}


int main()
{
    int sockfd;
    struct sockaddr_in serv_address, cli_address;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) > 0) //sockfd
        printf("The socket was created\n");
    serv_address.sin_family = AF_INET;
    serv_address.sin_addr.s_addr = INADDR_ANY;
    serv_address.sin_port = htons(16001);
    printf("The address before bind %s ...\n", inet_ntoa(serv_address.sin_addr));
    if (bind(sockfd, (struct sockaddr *)&serv_address, sizeof(serv_address)) == 0) //bind
        printf("Binding Socket\n");
    str_echo(sockfd, (struct sockaddr *)&cli_address, sizeof(cli_address));
    return 0;
}