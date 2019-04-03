//
//  Cup.h
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#ifndef Cup_h
#define Cup_h

#include "../src/Config.h"

class Cup{
private:
    int id;
    Eigen::Vector3d center_;
    double radius_;
    double height_;
    double weight_;

    Eigen::Vector3d X_axis_;
    Eigen::Vector3d Y_axis_;
    Eigen::Vector3d Z_axis_;
    
    Eigen::Isometry3d WorldToCup_;//这个是自己建系
    Eigen::Isometry3d CupToHand_;//这个是提前给定的
    
    int HandPara1,HandPara2,HandPara3,HandPara4,HandPara5,HandPara6;//手的六个参数
    
public:
    //Constructor
    Cup();
//    Cup(int id,Eigen::Vector3d center,double radius,double height,double weight,Eigen::Vector3d & Z_axis);//自动建系
    Cup(int id,Eigen::Vector3d center,double radius,double height,double weight,Eigen::Vector3d & X_axis,Eigen::Vector3d & Y_axis,Eigen::Vector3d & Z_axis);//给定系
    ~Cup();
    
    
    //Methods
    Eigen::Vector3d CupCordToWorldCord(Eigen::Vector3d & CupCord);
    
    Eigen::Vector3d HandCenterToCupCord();
    
    Eigen::Vector3d HandCenterToWorldCord();

};

#endif /* Cup_h */
