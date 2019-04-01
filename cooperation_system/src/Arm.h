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
    std::string port_;
    
public:
    //Constructor
    Arm();
    Arm(Config configuration);
    Arm(int id,std::string arm_ip, std::string arm_port);
    ~Arm();
    
    //Methods
    bool SendTcp(std::string Message) const;
    std::string ReceiveTcp() const;
    bool Arm_move() const;
    
    friend std::ostream & operator<<(std::ostream &os, const Arm &c);
    
};

#endif /* Arm_h */
