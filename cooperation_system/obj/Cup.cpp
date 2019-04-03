//
//  Cup.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/3.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include "Cup.h"


Cup::Cup(){
}


Cup::Cup(int id,Eigen::Vector3d center,double radius,double height,double weight,Eigen::Vector3d & X_axis,Eigen::Vector3d & Y_axis,Eigen::Vector3d & Z_axis){
    X_axis.normalize();
    Y_axis.normalize();
    Z_axis.normalize();
    
    center_ = center;
    X_axis_ = X_axis;
    Y_axis_ = Y_axis;
    Z_axis_ = Z_axis;
    radius_ = radius;
    height_ = height;
    weight_ = weight;
    
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix<<X_axis_,Y_axis_,Z_axis_;
    
    WorldToCup_ = Eigen::Isometry3d::Identity();                // 虽然称为3d，实质上是4＊4的矩阵
    WorldToCup_.rotate ( rotation_matrix );                                     // 按照rotation_vector进行旋转
    WorldToCup_.pretranslate ( center );
    
    
    CupToHand_ = Eigen::Isometry3d::Identity();                
//    CupToHand_.rotate ( rotation_matrix );
    CupToHand_.pretranslate ( Eigen::Vector3d ( -radius-1 , 0 , height/2 ) );
}

Cup::~Cup(){
}

Eigen::Vector3d Cup::CupCordToWorldCord(Eigen::Vector3d & CupCord){
    Eigen::Vector3d WorldCord = WorldToCup_ * CupCord;
    std::cout<<CupCord.transpose()<<" CupCordToWorldCord tranformed -> "<< WorldCord.transpose()<<std::endl;
    return WorldCord;
}

Eigen::Vector3d Cup::HandCenterToCupCord(){
    Eigen::Vector3d CupCord = CupToHand_ * Eigen::Vector3d::Zero();
    std::cout<<"HandCenterToCupCord tranformed -> "<< CupCord.transpose()<<std::endl;
    return CupCord;
}

Eigen::Vector3d Cup::HandCenterToWorldCord(){
    Eigen::Vector3d CupCord =HandCenterToCupCord();
    return CupCordToWorldCord(CupCord);
}
