//
//  Arm.h
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#ifndef Arm_h
#define Arm_h
#include "Config.h"

class Arm{
private:
    int id_;
    std::string ip_;
    unsigned short port_;
    bool status_;
    
    
    SocketDescriptor SocketDescriptor_;
    ServerAddress ServerAddress_;
    
public:
    //Constructor
    Arm();
    Arm(Config configuration);
    Arm(int id,std::string Arm_ip, unsigned short Arm_port);
    ~Arm();
    
    //Methods
    bool SendTcp(std::string Message) const;
    bool ReceiveTcp(std::string & Message) const;
    void Arm_move(std::string & Send) const;
    
    friend std::ostream & operator<<(std::ostream &os, const Arm &c);
    
};

#endif /* Arm_h */
