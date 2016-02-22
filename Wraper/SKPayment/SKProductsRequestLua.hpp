#ifndef SKPaymentQueueLua_hpp
#define SKPaymentQueueLua_hpp
#include "SKProductsRequestWraper.h"
#include "CCLuaEngine.h"

class SKProductsRequestLua:public SKProductsRequestWraper, public SKProductsRequestListener{
public:
    static SKProductsRequestLua *getInstance();
    static void destroyInstance();
public:
    SKProductsRequestLua();
    ~SKProductsRequestLua();
    void requestSKProducts(cocos2d::LUA_TABLE products, cocos2d::LUA_FUNCTION listener);
private:
    virtual void RequestSKProductsCallback(std::list<SKProductWraper*> products);
    cocos2d::LUA_FUNCTION m_listener;
};
#endif /* SKPaymentQueueLua_hpp */
