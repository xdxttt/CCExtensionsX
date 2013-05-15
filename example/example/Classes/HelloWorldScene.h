#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    void requestSKProductsCallBack(cocos2d::CCNode *node, void *data);
    void payCallBack(cocos2d::CCNode *node, void *data);
    void verifyCallBack(cocos2d::CCNode *node, void *data);
    void initRemoteNotificationCallBack(cocos2d::CCNode *node, void *data);
    void remoteNotification(cocos2d::CCNode *node, void *data);
    void getProductsConfCallBack(cocos2d::CCNode *node, void *data);

    
    void getConfCallBack(cocos2d::CCNode *node, void *data);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
