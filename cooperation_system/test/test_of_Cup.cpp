//
//  test_of_Cup.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/3.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include <iostream>
#include "../obj/Cup.h"

int main(){
    Eigen::Vector3d center(100,200,300);
    Eigen::Vector3d X_axis(0,0,1);
    Eigen::Vector3d Y_axis(0,1,0);
    Eigen::Vector3d Z_axis(-1,0,0);
    
    Cup cup1 ={1,center,5.1,6.8,78.0,X_axis ,Y_axis,Z_axis};
    
    cup1.HandCenterToWorldCord();

    
}


