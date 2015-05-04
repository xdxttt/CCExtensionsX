//
//  CCConfig.h
//
//

#ifndef __CCConfig__
#define __CCConfig__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class CCConfig :public cocos2d::CCObject{
public:
    static CCConfig *getInstance();
    static void destroyInstance();
public:

    void setupServiceAddress(const char* address);
    void setupSecretKey(const char* secretKey);
    void setupAppID(const char* appID);

    //  extension::CCHttpResponse *response  = (extension::CCHttpResponse *)data;
    void getModelConf(const char *model,CCObject* pTarget, SEL_CallFuncND pSelector);
    
public:
        CCConfig();
    ~CCConfig();
private:
    std::string address;
    std::string secretKey;
    std::string appID;

};
#endif /* defined(__CCConfig__) */
