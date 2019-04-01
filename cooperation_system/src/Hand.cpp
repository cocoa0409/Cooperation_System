//
//  Hand.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include "Hand.h"

Hand::Hand(){
    id_=0;
    ip_="192.168.0.1";
    port_="6666";
}

Hand::Hand(Config configuration){
    
}

Hand::Hand(int id,std::string hand_ip, std::string hand_port){
    id_=id;
    ip_=hand_ip;
    port_=hand_port;
}

Hand::~Hand(){
}

std::ostream & operator<<(std::ostream &os, const Hand &c){
    os<<"Hand No."<<c.id_<<std::endl<<"IP: "+c.ip_<<std::endl<<"Port: "+c.port_<<std::endl;
    return os;
}

