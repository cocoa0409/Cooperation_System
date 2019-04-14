//
//  Cup.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/3.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include "Cup.h"
#define ANGEL_UNKNOWN 15
#define THETA 0.432669


std::string findDirection(Eigen::Vector3d & Z_axis,double epsilon);
Eigen::Vector3d findYaxis(Eigen::Vector3d & center,Eigen::Vector3d & Z_axis,std::string & Direction_of_Z_axis);
Eigen::Vector3d findXaxis(Eigen::Vector3d & Y_axis, Eigen::Vector3d & Z_axis);
Eigen::Isometry3d findWorldToCup(Eigen::Vector3d & center,Eigen::Vector3d & X_axis,Eigen::Vector3d & Y_axis,Eigen::Vector3d & Z_axis);
Eigen::Isometry3d findCupToHand(double radius, double height,double experience, std::string & Direction_of_Z_axis);

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
    
    Direction_of_Z_axis_ = findDirection(Z_axis_, 0.05);
    std::cout<<"建系方式 : "<<Direction_of_Z_axis_<<std::endl;
    Y_axis_ = findYaxis(center_, Z_axis_ , Direction_of_Z_axis_);
    X_axis_ = findXaxis(Y_axis_, Z_axis_);
    WorldToCup_ = findWorldToCup(center_, X_axis_, Y_axis_, Z_axis_);
    
    
    CupToHand_ = findCupToHand(radius_, height_, 0.5 , Direction_of_Z_axis_); // exp0.5
    
    
    
    ROTATIONWorldToHand_ = WorldToCup_.rotation() * CupToHand_.rotation();
    EulerAngleWorldToHand_ = ROTATIONWorldToHand_.eulerAngles ( 2,1,0 ); //ZYX
    HandCenterToWorldCord_ = HandCenterToWorldCord();
    
    HandPara1_ = 800;
    HandPara2_ = 800;
    HandPara3_ = 800;
    HandPara4_ = 800;
    HandPara5_ = 800;
    HandPara6_ = 2000;
}

std::string findDirection(Eigen::Vector3d & Z_axis,double epsilon){
    double NormCrossBetweenZaxisAndZ = Z_axis.dot(Eigen::Vector3d(0,0,1)); //通过NormCrossBetweenZaxisAndZ判断建系方式
    if(NormCrossBetweenZaxisAndZ <= -1+epsilon || NormCrossBetweenZaxisAndZ >= 1-epsilon){
        return "perpendicular";
    }
    else{
        return "oblique";
    }
}

Eigen::Vector3d findYaxis(Eigen::Vector3d & center,Eigen::Vector3d & Z_axis,std::string & Direction_of_Z_axis){
    if(Direction_of_Z_axis == "perpendicular"){
        Z_axis=Eigen::Vector3d(0,0,1);
        Eigen::Vector3d Y (center[0],center[1],0);
        Y.normalize();
        assert( 0 == Z_axis.dot(Y));
        return Y;
    }
    else{
        assert( Direction_of_Z_axis == "oblique");
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

Eigen::Isometry3d findCupToHand(double radius, double height,double experience, std::string & Direction_of_Z_axis){
    Eigen::Isometry3d CupToHand;
    Eigen::Matrix3d rotation_matrix,THETA_OF_HAND;
    rotation_matrix<<1,0,0,0,0,1,0,-1,0;
    CupToHand = Eigen::Isometry3d::Identity();
//    double ANGLE_OF_HANDS_THUMB_AND_INDEXFINGER= ANGEL_UNKNOWN*M_PI/180;
    
    if(Direction_of_Z_axis == "perpendicular"){//垂直建系
        CupToHand.rotate ( rotation_matrix );
        CupToHand.pretranslate( Eigen::Vector3d( -radius-experience*2 ,abs(-radius/tan(M_PI/6)+6)-experience, height/2 ));//做个偏移
        //    CupToHand.pretranslate(Eigen::Vector3d( -radius-experience*2 ,0, height/2 ));
    }
    else{//歪斜建系
        assert( Direction_of_Z_axis == "oblique");
//        double THETA = atan2(9.5*sin(ANGLE_OF_HANDS_THUMB_AND_INDEXFINGER),14.5-9.5*cos(ANGLE_OF_HANDS_THUMB_AND_INDEXFINGER));
        std::cout<<THETA;
        THETA_OF_HAND <<cos(THETA),-sin(THETA),0,sin(THETA),cos(THETA),0,0,0,1;
        
        CupToHand.rotate( THETA_OF_HAND.transpose() * rotation_matrix  );
        CupToHand.pretranslate (THETA_OF_HAND.transpose()* Eigen::Vector3d( -radius-experience*2 ,abs(-radius/tan(M_PI/6)+6)-experience, height/2 ));
    }
    return CupToHand;
}

Cup::~Cup(){
}

Eigen::Vector3d Cup::CupCordToWorldCord(Eigen::Vector3d & CupCord){
    Eigen::Vector3d WorldCord = WorldToCup_ * CupCord;
//    std::cout<<CupCord.transpose()<<" CupCordToWorldCord tranformed -> "<< WorldCord.transpose()<<std::endl;
    return WorldCord;
}

Eigen::Vector3d Cup::HandCordToWorldCord(Eigen::Vector3d & HandCord){
    Eigen::Vector3d CupCord = WorldToCup_ * CupToHand_ * HandCord;
    return CupCord;
    
}

Eigen::Vector3d Cup::HandCenterToCupCord(){
    Eigen::Vector3d CupCord = CupToHand_ * Eigen::Vector3d::Zero();
//    std::cout<<"HandCenterToCupCord tranformed -> "<< CupCord.transpose()<<std::endl;
    return CupCord;
}
Eigen::Vector3d Cup::HandCenterToWorldCord(){
    Eigen::Vector3d CupCord =HandCenterToCupCord();
    return CupCordToWorldCord(CupCord);
}


std::vector<KeyPoint> Cup::PathPlanning(){
    std::vector<KeyPoint> RoadPoints;
    
    if(Direction_of_Z_axis_ == "perpendicular"){//垂直建系
        Eigen::Vector3d BASE_Z_UP_HandCenterToWorld = HandCenterToWorldCord_;
        BASE_Z_UP_HandCenterToWorld[2] += 20;
        
        KeyPoint KP1= {BASE_Z_UP_HandCenterToWorld,EulerAngleWorldToHand_};
        KeyPoint kp_dest={HandCenterToWorldCord_,EulerAngleWorldToHand_,HandPara1_,HandPara2_,HandPara3_,HandPara4_,HandPara5_,HandPara6_};
        
        RoadPoints.push_back(KP1);
        RoadPoints.push_back(kp_dest);
    }
    else{//歪斜建系
        assert( Direction_of_Z_axis_ == "oblique");
        Eigen::Vector3d BASE_Z_UP_HandCenterToWorld = HandCenterToWorldCord_;
        BASE_Z_UP_HandCenterToWorld[2] += 20;
        KeyPoint KP1= {BASE_Z_UP_HandCenterToWorld,EulerAngleWorldToHand_};
        KeyPoint kp_dest={HandCenterToWorldCord_,EulerAngleWorldToHand_,HandPara1_,HandPara2_,HandPara3_,HandPara4_,HandPara5_,HandPara6_};
        
        RoadPoints.push_back(KP1);
        RoadPoints.push_back(kp_dest);
        RoadPoints.push_back(KP1);
        RoadPoints.push_back(kp_dest);
        RoadPoints.push_back(KP1);
        RoadPoints.push_back(kp_dest);
    }

    return RoadPoints;
}
