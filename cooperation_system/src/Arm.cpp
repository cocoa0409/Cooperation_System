//
//  Arm.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include "Arm.h"

Arm::Arm(){
    status_=false;
}

Arm::Arm(Config configuration){
}

Arm::Arm(int id,std::string Arm_ip, unsigned short Arm_port){
    id_ = id;
    ip_ = Arm_ip;
    port_ = Arm_port;
    status_ = false;
    try{
        SocketDescriptor_ = socket(AF_INET, SOCK_STREAM, 0);
        if(-1 == SocketDescriptor_){
            throw "<Arm>|<socket fail> ! ";
        }
    }
    catch(const char* msg){
        std::cerr<<msg<<std::endl;
        exit(90);
    }
    
    std::cout<<"<Arm>|socket ok! "<<std::endl;
    
    bzero(&ServerAddress_,sizeof(ServerAddress));
    ServerAddress_.sin_family=AF_INET;
    ServerAddress_.sin_addr.s_addr= inet_addr(ip_.c_str());
    ServerAddress_.sin_port=htons(port_);
    
    try{
        if(-1 == connect(SocketDescriptor_,(struct sockaddr *)(&ServerAddress_), sizeof(struct sockaddr))){
            throw "<Arm>|<connect fail> ! ";
        }
    }
    catch(const char* msg){
        std::cerr<<msg<<std::endl;
        exit(91);
    }
    
    std::cout<<"<Arm>|connect ok! "<<std::endl;
    status_ = true;
}

Arm::~Arm(){
    if(-1 == close(SocketDescriptor_)){
        std::cout<<"<Arm>|close ok! "<<std::endl;
    }
}

bool Arm::SendTcp(std::string message) const{
    try{
        if( -1 == send(SocketDescriptor_,message.c_str(),message.size(),0)){
            throw "<Arm>|<send fail> ! ";
        }
    }
    catch(const char* msg){
        std::cerr<<msg<<std::endl;
        exit(100);
    }
    std::cout<<"<Arm>|--send ok! : "+message<<std::endl;
    return true;
}

bool Arm::ReceiveTcp(std::string & message) const{
    char buffer[1024]="0";
    try{
        if( -1 == recv(SocketDescriptor_,buffer,1024,0)){
            throw "<Arm>|<receive fail> ! ";
        }
    }
    catch(const char* msg){
        std::cerr<<msg<<std::endl;
        exit(101);
    }
    std::cout<<"<Arm>|---receive ok! : "<<buffer<<std::endl;
    message = buffer;
    return true;
    
}

void Arm::Arm_move(std::string & Send) const{
    std::string Recv = "" ;
    SendTcp(Send);
    ReceiveTcp(Recv);
    if ( Recv == "okarm"){
        std::cout<<"<Arm>|-----move ok! : "+Send<<std::endl;
    }
}

std::ostream & operator<<(std::ostream &os, const Arm &c){
    os<<"Arm No."<<c.id_<<std::endl<<"IP: "+c.ip_<<std::endl<<"Port: "<<c.port_ <<std::endl;
    return os;
}

