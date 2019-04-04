//
//  KeyPoint.h
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/4.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#ifndef KeyPoint_h
#define KeyPoint_h
#include "Config.h"

class KeyPoint{
private:
    Eigen::Vector3d HandCenterINWorldCord_;
    Eigen::Vector3d EulerAngleWorldToHand_;
    bool HandMoveOrNot_;
    int HandPara1_,HandPara2_,HandPara3_,HandPara4_,HandPara5_,HandPara6_;//手的六个参数

public:
    KeyPoint();
    KeyPoint(Eigen::Vector3d HandCenterINWorldCord,Eigen::Vector3d EulerAngleWorldToHand,int HandPara1,int HandPara2,int HandPara3,int HandPara4,int HandPara5,int HandPara6);
    KeyPoint(Eigen::Vector3d HandCenterINWorldCord,Eigen::Vector3d EulerAngleWorldToHand);
    ~KeyPoint();
    
    std::string TransKPToHandMessage();
    std::string TransKPToArmMessage();
    bool HandMoveOrNot();
};

#endif /* KeyPoint_h */
