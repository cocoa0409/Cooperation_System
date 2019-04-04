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
#include "../src/KeyPoint.h"

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
    

    Eigen::Isometry3d WorldToCup_;//这个是自己建 物体坐标系相对于基坐标系
    Eigen::Isometry3d CupToHand_;//这个是 机械手坐标系相对于物体坐标系
    
    int HandPara1_,HandPara2_,HandPara3_,HandPara4_,HandPara5_,HandPara6_;//手的六个参数
    Eigen::Matrix3d ROTATIONWorldToHand_; //最关键 代表了从世界坐标系到机器手坐标系所需的旋转
    Eigen::Vector3d EulerAngleWorldToHand_; //最关键 代表了从世界坐标系到机器手坐标系的欧拉角
    Eigen::Vector3d HandCenterToWorldCord_;
    
public:
    //Constructor
    Cup();
    Cup(int id,Eigen::Vector3d center,double radius,double height,double weight,Eigen::Vector3d & Z_axis);//自动建系
    Cup(int id,Eigen::Vector3d center,double radius,double height,double weight,Eigen::Vector3d & X_axis,Eigen::Vector3d & Y_axis,Eigen::Vector3d & Z_axis);//给定系
    ~Cup();
    
    //Methods
    Eigen::Vector3d CupCordToWorldCord(Eigen::Vector3d & CupCord);
    Eigen::Vector3d HandCenterToCupCord();
    Eigen::Vector3d HandCenterToWorldCord();

    
    Eigen::Matrix3d getRotationWorldToHand(){return ROTATIONWorldToHand_;};
    Eigen::Vector3d getEulerAngleWorldToHand(){return EulerAngleWorldToHand_;};
    
    std::vector<KeyPoint> PathPlanning();
    

};

#endif /* Cup_h */
