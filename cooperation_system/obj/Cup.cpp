//
//  Cup.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/3.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include "Cup.h"

Eigen::Vector3d AUTOfindYaxis(Eigen::Vector3d & center,Eigen::Vector3d & Z_axis,double epsilon);
Eigen::Vector3d findXaxis(Eigen::Vector3d & Y_axis, Eigen::Vector3d & Z_axis);
Eigen::Isometry3d findWorldToCup(Eigen::Vector3d & center,Eigen::Vector3d & X_axis,Eigen::Vector3d & Y_axis,Eigen::Vector3d & Z_axis);
Eigen::Isometry3d findCupToHand(double radius, double height,double experience=1);

Cup::Cup(){
    ROTATIONWorldToHand_ = Eigen::Matrix3d::Identity();
    EulerAngleWorldToHand_ = Eigen::Vector3d::Identity();
}

//给定 z轴、原点q 情况下自动建系
Cup::Cup(int id,Eigen::Vector3d center,double radius,double height,double weight,Eigen::Vector3d & Z_axis){
    Z_axis.normalize();
    center_ = center;
    Z_axis_ = Z_axis;
    radius_ = radius;
    height_ = height;
    weight_ = weight;
    
    Y_axis_ = AUTOfindYaxis(center_, Z_axis_ , 0.05);
    X_axis_ = findXaxis(Y_axis_, Z_axis_);
    WorldToCup_ = findWorldToCup(center_, X_axis_, Y_axis_, Z_axis_);
    CupToHand_ = findCupToHand(radius_, height_,1);
    
    ROTATIONWorldToHand_ = WorldToCup_.rotation() * CupToHand_.rotation();
    EulerAngleWorldToHand_ = ROTATIONWorldToHand_.eulerAngles ( 2,1,0 ); //ZYX
    
}

Eigen::Vector3d AUTOfindYaxis(Eigen::Vector3d & center,Eigen::Vector3d & Z_axis,double epsilon){
    double NormCrossBetweenZaxisAndZ = Z_axis.dot(Eigen::Vector3d(0,0,1)); //通过NormCrossBetweenZaxisAndZ判断建系方式
    if(NormCrossBetweenZaxisAndZ <= -1+epsilon || NormCrossBetweenZaxisAndZ >= 1-epsilon){
        Z_axis=Eigen::Vector3d(0,0,1);
        Eigen::Vector3d Y (center[0],center[1],0);
        Y.normalize();
        assert( 0 == Z_axis.dot(Y));
        return Y;
    }
    else{
        Eigen::Vector3d Y = - Z_axis.cross(Eigen::Vector3d(0,0,1));
        Y.normalize();
        assert( 0 == Z_axis.dot(Y));
        return Y;
    }
}

Eigen::Vector3d findXaxis(Eigen::Vector3d & Y_axis, Eigen::Vector3d & Z_axis){
    return Y_axis.cross(Z_axis);
}

Eigen::Isometry3d findWorldToCup(Eigen::Vector3d & center,Eigen::Vector3d & X_axis,Eigen::Vector3d & Y_axis,Eigen::Vector3d & Z_axis){
    
    Eigen::Isometry3d WorldToCup;
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix<<X_axis,Y_axis,Z_axis;
    
    WorldToCup = Eigen::Isometry3d::Identity();                // 虽然称为3d，实质上是4＊4的矩阵
    WorldToCup.rotate ( rotation_matrix );                                     // 按照rotation_vector进行旋转
    WorldToCup.pretranslate ( center );
    
    return WorldToCup;
}

Eigen::Isometry3d findCupToHand(double radius, double height,double experience){
    Eigen::Isometry3d CupToHand;
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix<<1,0,0,0,0,1,0,-1,0;
    
    CupToHand = Eigen::Isometry3d::Identity();
    CupToHand.rotate ( rotation_matrix );
    CupToHand.pretranslate( Eigen::Vector3d( -radius-experience ,0, height/2 ));
    
    return CupToHand;
}



//给定 x y z轴、原点 情况下
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
    
    WorldToCup_ = findWorldToCup(center_, X_axis_, Y_axis_, Z_axis_);
    CupToHand_ = findCupToHand(radius_, height_,1);
    
    ROTATIONWorldToHand_ = WorldToCup_.rotation() * CupToHand_.rotation();
    EulerAngleWorldToHand_ = ROTATIONWorldToHand_.eulerAngles ( 2,1,0 ); //ZYX
    
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

