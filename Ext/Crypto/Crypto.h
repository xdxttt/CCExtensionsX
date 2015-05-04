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

class Crypto :public cocos2d::Ref{
public:
    static Crypto *getInstance();
    static void destroyInstance();
    std::string md5(const char *src,int len);

public:
    Crypto();
    ~Crypto();
};
#endif /* defined(__Crypto__) */
