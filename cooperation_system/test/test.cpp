//
//  test.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/3.
//  Copyright © 2019 兆吉 王. All rights reserved.
//


#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
// Eigen 几何模块
#include <Eigen/Geometry>

int main ( int argc, char** argv )
{
    Eigen::Vector3d A( 1,3,4 );
    Eigen::Vector3d B( 2,3,4 );
    Eigen::Vector3d C( 3,3,4 );
    Eigen::Matrix3d rotation_matrix;
    A.normalize();
    B.normalize();
    C.normalize();
    
    rotation_matrix<<A,B,C;
    cout<<rotation_matrix<<endl;
    
    Eigen::Isometry3d T=Eigen::Isometry3d::Identity();                // 虽然称为3d，实质上是4＊4的矩阵
//    T.rotate ( rotation_matrix );                                     // 按照rotation_vector进行旋转
    T.pretranslate ( Eigen::Vector3d ( 1,3,4 ) );
    
    
    cout << "Transform matrix = \n" << T.matrix() <<endl;
    
    Eigen::Vector3d v1 ( 1,0,0 );
    cout<<"v1 tranformed = "<<(T*Eigen::Vector3d::Zero())<<endl;
    cout<<"v1 tranformed = "<<(T*Eigen::Vector3d::Zero()).transpose()<<endl;
    
    
}
