//
//  KeyPoint.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/4.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include "KeyPoint.h"

KeyPoint::KeyPoint(){
}
KeyPoint::KeyPoint(Eigen::Vector3d HandCenterINWorldCord,Eigen::Vector3d EulerAngleWorldToHand,int HandPara1,int HandPara2,int HandPara3,int HandPara4,int HandPara5,int HandPara6){
    
    HandCenterINWorldCord_ = HandCenterINWorldCord;
    EulerAngleWorldToHand_ = EulerAngleWorldToHand;
    HandMoveOrNot_ = true;
    HandPara1_ = HandPara1;
    HandPara2_ = HandPara2;
    HandPara3_ = HandPara3;
    HandPara4_ = HandPara4;
    HandPara5_ = HandPara5;
    HandPara6_ = HandPara6;

}

KeyPoint::KeyPoint(Eigen::Vector3d HandCenterINWorldCord,Eigen::Vector3d EulerAngleWorldToHand){
    HandCenterINWorldCord_ = HandCenterINWorldCord;
    EulerAngleWorldToHand_ = EulerAngleWorldToHand;
    HandMoveOrNot_ = false;
    HandPara1_ = 0;
    HandPara2_ = 0;
    HandPara3_ = 0;
    HandPara4_ = 0;
    HandPara5_ = 0;
    HandPara6_ = 0;
}

KeyPoint::~KeyPoint(){
}

std::string KeyPoint::TransKPToHandMessage(){
    std::ostringstream out;
    out.precision(0);
    out<<std::fixed;
    out<<HandPara1_<<","<<HandPara2_<<","<<HandPara3_<<","<<HandPara4_<<","<<HandPara5_<<","<<HandPara6_;
    std::string str= out.str();
    return str;
    
}

std::string KeyPoint::TransKPToArmMessage(){
    std::ostringstream out;
    out.precision(6);
    out<<std::fixed;
    out<<HandCenterINWorldCord_[0]/100<<","<<HandCenterINWorldCord_[1]/100<<","<<HandCenterINWorldCord_[2]/100<<","<<EulerAngleWorldToHand_[0]*(180/M_PI)<<","<<EulerAngleWorldToHand_[1]*(180/M_PI)<<","<<EulerAngleWorldToHand_[2]*(180/M_PI);
    std::string str= out.str();
    return str;
}

bool KeyPoint::HandMoveOrNot(){
    return HandMoveOrNot_;
}

