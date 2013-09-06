//
//  xGameTools.cpp
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-5-7.
//
//

#include "Gift.h"
#include "HttpClient.h"
#include "Crypto.h"
using namespace cocos2d::extension;

CCGift* sGift = NULL;

CCGift *CCGift::getInstance(){
    if (sGift==NULL) {
        sGift = new CCGift;
    }
    return sGift;
}
void CCGift::destroyInstance(){
    if (sGift) {
        delete sGift;
    }
}
CCGift::CCGift(){
    
}
CCGift::~CCGift(){
    
}

void CCGift::setupServiceAddress(const char* address){
    this->address = address;
}
void CCGift::setupServiceToken(const char *token){
    this->token = token;
}

void CCGift::exchange(const char *code, cocos2d::CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *request = new CCHttpRequest;
    std::string url ="";
    url.append(address);
    url.append("/code/takeGift/");
    url.append(code);
    request->setUrl(url.c_str());
    
    std::string sign = CCCrypto::getInstance()->md5(url.append(token).c_str(),url.append(token).length());
    std::string postData = "";
    postData.append("sign=").append(sign);
    request->setRequestData(postData.c_str(), postData.length());

    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(pTarget,pSelector);
    CCHttpClient::getInstance()->send(request);
}