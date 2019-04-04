//
//  test_of_ControlSystem.cpp
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/4.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#include "../src/ControlSystem.h"



int main ( int argc, char** argv )
{
    Hand hand1={1,"127.0.0.1",3001};
    Arm arm1={1,"127.0.0.1",3000};
    ControlSystem CS={hand1,arm1};
    
    string RECV;
    CS.hand_.ReceiveTcp(RECV);
    CS.arm_.ReceiveTcp(RECV);
    
    KeyPoint kp1={Eigen::Vector3d (1,2,3),Eigen::Vector3d (4,5,6),500,501,502,503,504,505};
    KeyPoint kp2={Eigen::Vector3d (11,12,13),Eigen::Vector3d (14,15,16)};
    KeyPoint kp3={Eigen::Vector3d (21,22,23),Eigen::Vector3d (24,25,26),609,1808,1502,203,704,905};
    KeyPoint kp4={Eigen::Vector3d (31,32,33),Eigen::Vector3d (34,35,36),1500,1701,62,203,304,305};
    
    vector<KeyPoint> VKP={kp1,kp2,kp3,kp4};
    CS.move(VKP);
    
    getchar();
}
