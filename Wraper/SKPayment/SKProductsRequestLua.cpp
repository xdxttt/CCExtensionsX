//
//  SKPaymentQueueLua.cpp
//  cocos2d_lua_bindings
//
//  Created by xudexin on 15/12/31.
//
//

#include "SKProductsRequestLua.hpp"
SKProductsRequestLua *s_SKPaymentQueueLua = NULL;
SKProductsRequestLua::SKProductsRequestLua(){
}
SKProductsRequestLua::~SKProductsRequestLua(){
}
void SKProductsRequestLua::destroyInstance()
{
    if (s_SKPaymentQueueLua) {
        delete s_SKPaymentQueueLua;
    }
}

SKProductsRequestLua* SKProductsRequestLua::getInstance()
{
    if (s_SKPaymentQueueLua == NULL) {
        s_SKPaymentQueueLua = new SKProductsRequestLua();
    }
    return s_SKPaymentQueueLua;
}
void SKProductsRequestLua::RequestSKProductsCallback(std::list<SKProductWraper*> products){
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    cocos2d::LuaValueArray products_;

    for (std::list<SKProductWraper*>::iterator iter; iter!=products.end(); iter++) {
        SKProductWraper* product = *iter;
        
        cocos2d::LuaValueDict product_;
        product_["localizedDescription"] = cocos2d::LuaValue::stringValue(product->localizedDescription);
        product_["localizedTitle"] = cocos2d::LuaValue::stringValue(product->localizedTitle);
        product_["priceLocale"] = cocos2d::LuaValue::stringValue(product->priceLocale);
        product_["price"] = cocos2d::LuaValue::floatValue(product->price);
        product_["productIdentifier"] = cocos2d::LuaValue::stringValue(product->productIdentifier);
        products_.push_back(cocos2d::LuaValue::dictValue(product_));

        stack->pushLuaValueArray(products_);
        stack->executeFunctionByHandler(m_listener, 1);
    }
}
