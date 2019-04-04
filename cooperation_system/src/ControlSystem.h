//
//  ControlSystem.h
//  cooperation_system
//
//  Created by 兆吉 王 on 2019/4/1.
//  Copyright © 2019 兆吉 王. All rights reserved.
//

#ifndef ControlSystem_h
#define ControlSystem_h
#include "Hand.h"
#include "Arm.h"
#include "KeyPoint.h"
#include "Config.h"

class ControlSystem{
public:
    
    Hand hand_;
    Arm arm_;
    
    ControlSystem();
    ControlSystem(Hand & hand, Arm & arm);
    ~ControlSystem();
    
    
    void move(std::vector<KeyPoint> & keypoints);
    
    
    
    
};

#endif /* ControlSystem_h */
