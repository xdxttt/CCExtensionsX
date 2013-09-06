//
//  CCGift.h
//
//

#ifndef __CCGift__
#define __CCGift__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class CCGift :public cocos2d::CCObject{
public:
    static CCGift *getInstance();
    static void destroyInstance();
public:

    void setupServiceAddress(const char* address);
    void setupServiceToken(const char* token);
    
    //  extension::CCHttpResponse *response  = (extension::CCHttpResponse *)data;
    void exchange(const char *code,CCObject* pTarget, SEL_CallFuncND pSelector);
    
public:
    CCGift();
    ~CCGift();
private:
    std::string address;
    std::string token;

};
#endif /* defined(__CCGift__) */
