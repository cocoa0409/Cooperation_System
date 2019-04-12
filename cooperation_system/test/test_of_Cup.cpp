//
//  test_of_Cup.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/3.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include <iostream>
#include "../obj/Cup.h"

using namespace std;
int main(){
    Eigen::Vector3d center(100,200,300);
    //杯子平躺 Z轴方向指向(0,0,1)
    
    Eigen::Vector3d Z_axis(0,0,1);
    Z_axis.normalize();
    
    Cup cup1 ={1,center,5,10,78.0,Z_axis};
    cup1.HandCenterToWorldCord();

    //给出基坐标系到机械手坐标系的旋转
    cout<<cup1.getRotationWorldToHand()<<endl;
    
    //给出基坐标系到机械手坐标系的欧拉角
    cout<<cup1.getEulerAngleWorldToHand()<<endl;

    
}


