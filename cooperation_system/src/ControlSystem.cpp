//
//  ControlSystem.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include "ControlSystem.h"

ControlSystem::ControlSystem(){
}

ControlSystem::ControlSystem(Hand & hand, Arm & arm){
    hand_ = hand;
    arm_ = arm;
}


ControlSystem::~ControlSystem(){
}



void ControlSystem::move(std::vector<KeyPoint> & keypoints){
    int length = (int)keypoints.size();
    std::string HandMessage,ArmMessage;
    
    for(int j=1; j<=length ; j++){
        std::cout<<"---- step "<<j<<" ----"<<std::endl;
        if(keypoints[j-1].HandMoveOrNot() == true){
            HandMessage = keypoints[j-1].TransKPToHandMessage();
            ArmMessage = keypoints[j-1].TransKPToArmMessage();
            arm_. Arm_move(ArmMessage);
            hand_. Hand_move_withoutCertification(HandMessage);
            sleep(2);
        }
        else{
            ArmMessage = keypoints[j-1].TransKPToArmMessage();
            arm_. Arm_move(ArmMessage);
            sleep(0.05);
        }
    }
}
