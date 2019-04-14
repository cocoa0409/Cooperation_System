//
//  test_of_INSERT_GRASP.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/14.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include "ControlSystem.h"
#include "Cup.h"



int main ( int argc, char** argv )
{
    //初始化手
    //    Hand hand1={1,"10.16.250.19",3000};
    Hand hand1={1,"127.0.0.1",3000};
    //初始化臂
    Arm arm1={1,"192.168.1.100",6666};
    //
    //初始化控制系统
    ControlSystem CS={hand1,arm1};
    //
    //    //先receive一次保证正确
    std::string RECV;
    //    CS.hand_.ReceiveTcp(RECV);
    //    CS.arm_.ReceiveTcp(RECV);
    //
    //
    Eigen::Vector3d center(-25.54,-77.76,-4);
    
    Eigen::Vector3d Z_axis_2(-1,-1,0);
    
    
    Z_axis_2.normalize();
    Cup cup ={1,center,3.4,14,0,Z_axis_2};
    std::vector<KeyPoint> Road2= cup.PathPlanning();
    CS.move(Road2);
    
    
    getchar();
}

