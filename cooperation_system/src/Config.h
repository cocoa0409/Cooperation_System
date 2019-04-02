//
//  Config.h
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#ifndef Config_h
#define Config_h

#include <string>
#include <iostream>

//Scoket
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

typedef int SocketDescriptor;
typedef sockaddr_in ServerAddress;

class Config{
    
};

#endif /* Config_h */
