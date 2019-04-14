//
//  test.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/3.
//  Copyright © 2019 兆吉 王. All rights reserved.
//


#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#include "../src/ControlSystem.h"
#include "../obj/Cup.h"



int main ( int argc, char** argv )
{
    Arm arm1={1,"192.168.1.100",6666};
    std::string sendset1[5]={"0.017317,-0.644562,0.114096,-90,-44,-180","0.017317,-0.644562,0.134096,-90,-44,-180","0.017317,-0.644562,0.154096,-90,-44,-180","0.017317,-0.644562,0.174096,-90,-44,-180","0.017317,-0.644562,0.194096,-90,-44,-180"},res;
    for(int i=0;i<=4;i++){
        arm1.SendTcp(sendset1[i]);
        arm1.ReceiveTcp(res);
        std::cout<<res;
    
    }
    getchar();
}
