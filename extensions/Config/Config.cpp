//
//  xGameTools.cpp
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-5-7.
//
//

#include "Config.h"
#include "HttpClient.h"
#include "Crypto.h"
using namespace cocos2d::extension;

CCConfig* sConfig = NULL;

CCConfig *CCConfig::getInstance(){
    if (sConfig==NULL) {
        sConfig = new CCConfig;
    }
    return sConfig;
}
void CCConfig::destroyInstance(){
    if (sConfig) {
        delete sConfig;
    }
}
CCConfig::CCConfig(){
    
}
CCConfig::~CCConfig(){
    
}

void CCConfig::setupServiceAddress(const char* address){
    this->address = address;
}
void CCConfig::setupServiceToken(const char *token){
    this->token = token;
}

void CCConfig::getModelConf(const char *model,CCObject* pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *request = new CCHttpRequest;
    std::string url ="";
    url.append(address);
    url.append("/service/getModelConf/");
    url.append(model);
    request->setUrl(url.c_str());
    
    std::string sign = CCCrypto::getInstance()->md5(url.append(token).c_str(),url.append(token).length());
    std::string postData = "";
    postData.append("sign=").append(sign);
    request->setRequestData(postData.c_str(), postData.length());

    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(pTarget,pSelector);
    CCHttpClient::getInstance()->send(request);
}