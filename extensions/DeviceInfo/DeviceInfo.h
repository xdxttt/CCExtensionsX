//
//  CCDiviceInfo.h
//
//  Created by xudexin on 13-4-28.
//
//

#ifndef __CCDeviceInfo__
#define __CCDeviceInfo__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class CCDeviceInfo :public cocos2d::CCObject{
public:
    static CCDeviceInfo *getInstance();
    static void destroyInstance();
    std::string getUUID();
    
public:
    CCDeviceInfo();
    ~CCDeviceInfo();
};

#endif /* defined(__CCDeviceInfo__) */
