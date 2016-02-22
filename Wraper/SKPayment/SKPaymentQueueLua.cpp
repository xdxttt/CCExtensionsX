//
//  SKPaymentQueueLua.cpp
//  cocos2d_lua_bindings
//
//  Created by xudexin on 15/12/31.
//
//

#include "SKPaymentQueueLua.hpp"
SKPaymentQueueLua *s_SKPaymentQueueLua = NULL;
SKPaymentQueueLua::SKPaymentQueueLua(){
}
SKPaymentQueueLua::~SKPaymentQueueLua(){
}
void SKPaymentQueueLua::destroyInstance()
{
    if (s_SKPaymentQueueLua) {
        delete s_SKPaymentQueueLua;
    }
}

SKPaymentQueueLua* SKPaymentQueueLua::getInstance()
{
    if (s_SKPaymentQueueLua == NULL) {
        s_SKPaymentQueueLua = new SKPaymentQueueLua();
    }
    return s_SKPaymentQueueLua;
}

void SKPaymentQueueLua::purchase(std::string products_id,int quantity,cocos2d::LUA_FUNCTION listener){
    SKPaymentQueueWraper::getInstance()->purchase(this, products_id, quantity);
    if (m_listener)
    {
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(m_listener);
    }
    m_listener = listener;
}
void SKPaymentQueueLua::restorePurchase(cocos2d::LUA_FUNCTION listener){
    SKPaymentQueueWraper::getInstance()->restorePurchase(this);
    if (m_listener)
    {
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(m_listener);
    }
    m_listener = listener;
}

void SKPaymentQueueLua::completeTransaction(std::string transactionIdentifier){
    SKPaymentQueueWraper::getInstance()->completeTransaction(transactionIdentifier);
}

void SKPaymentQueueLua::UpdatedTransactionsCallBack(std::list<SKPaymentTransactionWraper*> appStorePaymentTransactions){

    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    cocos2d::LuaValueArray transactions_;

    for (std::list<SKPaymentTransactionWraper*>::iterator iter; iter!=appStorePaymentTransactions.end(); iter++) {
        SKPaymentTransactionWraper* transaction = *iter;
        cocos2d::LuaValueDict payment_;
        payment_["state"] = cocos2d::LuaValue::stringValue(transaction->payment.productIdentifier);
        payment_["requestData"] = cocos2d::LuaValue::stringValue((char*)transaction->payment.requestData);
        payment_["quantity"] = cocos2d::LuaValue::intValue((int)transaction->payment.quantity);
        
        cocos2d::LuaValueDict transaction_;
        transaction_["state"] = cocos2d::LuaValue::intValue(transaction->transactionState);
        transaction_["transactionIdentifier"] = cocos2d::LuaValue::stringValue(transaction->transactionIdentifier);
        transaction_["transactionDate"] = cocos2d::LuaValue::stringValue((char*)transaction->transactionDate);
        transaction_["transactionReceipt"] = cocos2d::LuaValue::stringValue(transaction->transactionReceipt);
        transaction_["error"] = cocos2d::LuaValue::stringValue(transaction->error);
        transaction_["payment"] =  cocos2d::LuaValue::dictValue(payment_);
        
        transactions_.push_back(cocos2d::LuaValue::dictValue(transaction_));
    }
    stack->pushLuaValueArray(transactions_);
    stack->executeFunctionByHandler(m_listener, 1);
}
