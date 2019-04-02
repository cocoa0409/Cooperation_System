//
//  Hand.h
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#ifndef Hand_h
#define Hand_h
#include "Config.h"

class Hand{
private:
    int id_;
    std::string ip_;
    unsigned short port_;
    bool status_;

    
    SocketDescriptor SocketDescriptor_;
    ServerAddress ServerAddress_;
    
public:
//Constructor
    Hand();
    Hand(Config configuration);
    Hand(int id,std::string Hand_ip, unsigned short Hand_port);
    ~Hand();
    
//Methods
    bool SendTcp(std::string Message) const;
    bool ReceiveTcp(std::string & Message) const;
    bool Hand_move() const;
    
    friend std::ostream & operator<<(std::ostream &os, const Hand &c);
    
};

#endif /* Hand_h */
