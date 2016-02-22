#ifndef SKPaymentQueueLua_hpp
#define SKPaymentQueueLua_hpp
#include "SKPaymentQueueWraper.h"
#include "CCLuaEngine.h"

class SKPaymentQueueLua:public SKPaymentQueueWraper, public SKPaymentQueueListener{
public:
    static SKPaymentQueueLua *getInstance();
    static void destroyInstance();
public:
    SKPaymentQueueLua();
    ~SKPaymentQueueLua();
    void purchase(std::string products_id,int quantity,cocos2d::LUA_FUNCTION listener);
    void restorePurchase(cocos2d::LUA_FUNCTION listener);
    void completeTransaction(std::string transactionIdentifier);
private:
    virtual void UpdatedTransactionsCallBack(std::list<SKPaymentTransactionWraper*> appStorePaymentTransactions);
    cocos2d::LUA_FUNCTION m_listener;
};
#endif /* SKPaymentQueueLua_hpp */
