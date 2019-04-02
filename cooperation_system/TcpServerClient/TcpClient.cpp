#include <stdio.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int cfd;
    
    struct sockaddr_in s_add;
    unsigned short portnum=3000;
    
    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == cfd)
    {
        printf("socket fail ! \r\n");
        return -1;
    }
    printf("socket ok !\r\n");
    
    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family=AF_INET;
    s_add.sin_addr.s_addr= inet_addr("127.0.0.1");
    s_add.sin_port=htons(portnum);
    printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);
    
    if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
    {
        printf("connect fail !\r\n");
        return -1;
    }
    printf("connect ok !\r\n");
    
    
    
    
    char message[1024];
    
    while(1){
        char buffer[1024]={0};
        std::cout<<"输入要向服务器发送的信息:";
        std::cin>>message;
        if( -1 == send(cfd,&message,strlen(message),0)){
            std::cout<<"send data fail!"<<std::endl;
            break;
        }
        if( -1 == recv(cfd,buffer,1024,0)){
            std::cout<<"receive data fail!"<<std::endl;
            break;
        }
        std::cout<<buffer<<std::endl;
    }
    close(cfd);
    return 0;
}
