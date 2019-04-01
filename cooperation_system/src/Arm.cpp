//
//  Arm.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//
#include "Arm.h"

Arm::Arm(){
    id_=0;
    ip_="192.168.0.1";
    port_="6666";
}

Arm::Arm(Config configuration){
    
}

Arm::Arm(int id,std::string arm_ip, std::string arm_port){
    id_=id;
    ip_=arm_ip;
    port_=arm_port;
}

Arm::~Arm(){
}

std::ostream & operator<<(std::ostream &os, const Arm &c){
    os<<"Arm No."<<c.id_<<std::endl<<"IP: "+c.ip_<<std::endl<<"Port: "+c.port_<<std::endl;
    return os;
}
