//
//  Crypto.h
//
//  Created by xudexin on 13-5-11.
//
//

#ifndef __Crypto__
#define __Crypto__

#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class CCCrypto :public cocos2d::CCObject{
public:
    static CCCrypto *getInstance();
    static void destroyInstance();
    std::string md5(const char *src,int len);

public:
    CCCrypto();
    ~CCCrypto();
};
#endif /* defined(__Crypto__) */
