//
//  RemoteNotification.h
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-4-28.
//
//

#ifndef __Ragnarok_Battle_Online__RemoteNotification__
#define __Ragnarok_Battle_Online__RemoteNotification__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class CCRemoteNotificationContent {
public:
    CCRemoteNotificationContent(){
        pTarget = NULL;
        pSelector = NULL;
    }
    ~CCRemoteNotificationContent(){
    }
    CCObject* pTarget;
    
    SEL_CallFuncND pSelector;
};

class CCRemoteNotification :public cocos2d::CCObject{
    
public:
    static CCRemoteNotification *getInstance();
    static void destroyInstance();
    
public:
    void setupServiceAddress(const char* address);
    void setupSecretKey(const char* secretKey);
    void setupAppID(const char* appID);
    
    void reportDiviceToken(const char *token,CCObject* pTarget, SEL_CallFuncND pSelector);
    
    //data  -> (char*)token
    int init(CCObject* pTarget, SEL_CallFuncND pSelector);
    //data  -> (char*)msessage
    int setNotificationHandler(CCObject* pTarget, SEL_CallFuncND pSelector);
    
public:
    
    CCRemoteNotification();
    ~CCRemoteNotification();
    
private:
    std::string address;
    std::string secretKey;
    std::string appID;
};


#endif /* defined(__Ragnarok_Battle_Online__RemoteNotification__) */
