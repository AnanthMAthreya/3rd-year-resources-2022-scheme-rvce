#include<sys/types.h> 
#include<sys/socket.h> 
#include<sys/stat.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<fcntl.h> 
#include<unistd.h> 
#include<netinet/in.h> 
#include<arpa/inet.h>

void str_echo(int connfd,int port)
{ 
    int n=1,bufsize = 1024,len; 
    char *buff = malloc(bufsize); 
    struct sockaddr_in addr;

    do{
        while((n=recv(connfd,buff,bufsize,0))>0)
        { 
            printf("From client connected to %d :",port); 
            fputs(buff,stdout); 
            printf("Reply to the client connected to %d :",port); 
            fgets(buff,bufsize,stdin); 
            send(connfd,buff,n,0); 
        } 
    }while(n>0);


}


int main()
{ 
    int listenfd,connfd,addrlen,pid; 
    struct sockaddr_in address; 
    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) > 0)
        printf("The socket was created\n"); 
    else 
        printf("Error in Socket creation\n");

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port= htons(15001);

    if( bind( listenfd,(struct sockaddr *)& address,sizeof(address)) ==0) 
        printf("Binding Socket\n");

    listen(listenfd, 3);

    for(;;)
    { 
        addrlen = sizeof(struct sockaddr_in); 
        connfd = accept(listenfd,(struct sockaddr *)& address,&addrlen);

        if(connfd>0)
            printf("A new client connected from port :%d \n",  address.sin_port); 
        else 
            printf("A new client's connection wasn't accepted\n");
        
        if((pid=fork())==0)
        { 
            close(listenfd); 
            str_echo(connfd,address.sin_port); 
            exit(0); 
        } 
        close(connfd); 
    } 
    return 0; 
} 
