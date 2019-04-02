//
//  test.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/2.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include <iostream>
#include "../src/Hand.h"
#include "../src/Arm.h"
int main(int argc, const char * argv[]){
    Hand hand1={1,"127.0.0.1",3000};
    std::string sendset1[5]={"hand_test1","hand_test2","hand_test3","hand_test4","hand_test5"},res;
    hand1.ReceiveTcp(res);
    
    for(int i=0;i<=4;i++){
        hand1.SendTcp(sendset1[i]);
        hand1.ReceiveTcp(res);
    }
    
    Arm arm1={1,"127.0.0.1",3000};
    std::string sendset2[5]={"arm_test1","arm_test2","arm_test3","arm_test4","arm_test5"};
    arm1.ReceiveTcp(res);
    for(int i=0;i<=4;i++){
        arm1.SendTcp(sendset2[i]);
        arm1.ReceiveTcp(res);
    }
    
    
    

    
    
}
