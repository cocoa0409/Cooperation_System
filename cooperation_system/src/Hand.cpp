//
//  Hand.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include "Hand.h"

Hand::Hand(){
    status_=false;
}

Hand::Hand(Config configuration){
}

Hand::Hand(int id,std::string hand_ip, unsigned short hand_port){
    id_ = id;
    ip_ = hand_ip;
    port_ = hand_port;
    status_ = false;
    try{
        SocketDescriptor_ = socket(AF_INET, SOCK_STREAM, 0);
        if(-1 == SocketDescriptor_){
            throw "<Hand>|<socket fail> ! ";
        }
    }
    catch(const char* msg){
        std::cerr<<msg<<std::endl;
        exit(90);
    }
    
    std::cout<<"<Hand>|socket ok! "<<std::endl;
    
    bzero(&ServerAddress_,sizeof(ServerAddress));
    ServerAddress_.sin_family=AF_INET;
    ServerAddress_.sin_addr.s_addr= inet_addr(ip_.c_str());
    ServerAddress_.sin_port=htons(port_);
    
    try{
        if(-1 == connect(SocketDescriptor_,(struct sockaddr *)(&ServerAddress_), sizeof(struct sockaddr))){
            throw "<Hand>|<connect fail> ! ";
        }
    }
    catch(const char* msg){
        std::cerr<<msg<<std::endl;
        exit(91);
    }
    
    std::cout<<"<Hand>|connect ok! "<<std::endl;
    status_ = true;
}

Hand::~Hand(){
    close(SocketDescriptor_);
    std::cout<<"<Hand>|close ok! "<<std::endl;
}

bool Hand::SendTcp(std::string message) const{
    try{
        if( -1 == send(SocketDescriptor_,&message,message.size()+1,0)){
            throw "<Hand>|<send fail> ! ";
        }
    }
    catch(const char* msg){
        std::cerr<<msg<<std::endl;
        exit(100);
    }
    std::cout<<"<Hand>|--send ok! : "+message<<std::endl;
    return true;
}

bool Hand::ReceiveTcp(std::string & message) const{
    char buffer[1024]="0";
    try{
        if( -1 == recv(SocketDescriptor_,buffer,1024,0)){
            throw "<Hand>|<receive fail> ! ";
        }
    }
    catch(const char* msg){
        std::cerr<<msg<<std::endl;
        exit(101);
    }
    std::cout<<"<Hand>|---receive ok! : "<<buffer<<std::endl;
    message = buffer;
    return true;
    
}


std::ostream & operator<<(std::ostream &os, const Hand &c){
    os<<"Hand No."<<c.id_<<std::endl<<"IP: "+c.ip_<<std::endl<<"Port: "<<c.port_ <<std::endl;
    return os;
}

