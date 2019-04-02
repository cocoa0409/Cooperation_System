//
//  main.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include <iostream>

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


int main(int argc, const char * argv[])
{
    
    int sfp,nfp;
    struct sockaddr_in s_add,c_add;
    unsigned int sin_size;
    
    unsigned short portnum=3000;
    printf("Hello,welcome to my server !\r\n");
    sfp = socket(AF_INET, SOCK_STREAM, 0);
    //    std::cout<<sfp<<std::endl;
    if(-1 == sfp)
    {
        printf("socket fail ! \r\n");
        return -1;
    }
    printf("socket ok !\r\n");
    
    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family=AF_INET;
    //    s_add.sin_addr.s_addr= inet_addr("");
    s_add.sin_addr.s_addr=htonl(INADDR_ANY);
    //这里应该是目的地址，只监听从这个地址发到端口的信息
    s_add.sin_port=htons(portnum);
    
    if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
    {
        printf("bind fail !\r\n");
        return -1;
    }
    printf("bind ok !\r\n");
    
    if(-1 == listen(sfp,5))
    {
        printf("listen fail !\r\n");
        return -1;
    }
    printf("listen ok\r\n");
    
    
    sin_size = sizeof(struct sockaddr_in);
    nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);
    if(-1 == nfp)
    {
        printf("accept fail !\r\n");
        return -1;
    }
    printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n",ntohl(c_add.sin_addr.s_addr),ntohs(c_add.sin_port));
    
    
    std::string message;
    while(1){
        char buffer[1024]={0};
        if(-1==recv(nfp,buffer,1024,0)){
            std::cout<<"recv fail !"<<std::endl;
            break;
        }
        std::cout<<buffer<<std::endl;
        
        std::cout<<"输入要向客户端发送的信息:";
        std::cin>>message;
        if( -1 == send(nfp,&message,message.size()+1,0)){
            std::cout<<"send data fail!"<<std::endl;
            return -1;
        }
        
        
    }
    
    close(nfp);
    close(sfp);
    return 0;
}
