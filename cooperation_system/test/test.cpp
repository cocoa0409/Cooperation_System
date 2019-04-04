//
//  test.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/3.
//  Copyright © 2019 兆吉 王. All rights reserved.
//


#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#include "../src/ControlSystem.h"
#include "../obj/Cup.h"



int main ( int argc, char** argv )
{
    Hand hand1={1,"127.0.0.1",3001};
    Arm arm1={1,"127.0.0.1",3000};
    ControlSystem CS={hand1,arm1};

    string RECV;
    CS.hand_.ReceiveTcp(RECV);
    CS.arm_.ReceiveTcp(RECV);
    //先receive一次保证正确
    

    Eigen::Vector3d Z_axis(1,1,0);
    Z_axis.normalize();
    Eigen::Vector3d center(100,200,300);
    Cup cup1 ={1,center,5,10,0,Z_axis};
    vector<KeyPoint> Road= cup1.PathPlanning();
    CS.move(Road);
    
    
    Eigen::Vector3d Z_axis_2(0,0,1);
    Cup cup2 ={1,center,5,10,0,Z_axis_2};
    vector<KeyPoint> Road2= cup2.PathPlanning();
    CS.move(Road2);
    
    
    getchar();
}
