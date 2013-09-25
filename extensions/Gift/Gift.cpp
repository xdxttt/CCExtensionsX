#include "Gift.h"
#include "HttpClient.h"
#include "Crypto.h"
#include "DeviceInfo.h"

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
void CCGift::setupSecretKey(const char *secretKey){
    this->secretKey = secretKey;
}
void CCGift::setupAppID(const char *appID){
    this->appID = appID;
}

void CCGift::exchange(const char *code, cocos2d::CCObject *pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *request = new CCHttpRequest;
    std::string url ="";
    url.append(address);
    url.append("/servicecode/takeGift/");
    url.append(appID);
    url.append("/");
    url.append(code);
    url.append("/");
    url.append(CCDeviceInfo::getInstance()->getUUID());
    
    request->setUrl(url.c_str());
   
    url.append(secretKey).c_str();
    std::string sign = CCCrypto::getInstance()->md5(url.c_str(),url.length());

    std::string postData = "";
    postData.append("sign=").append(sign);
    request->setRequestData(postData.c_str(), postData.length());

    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(pTarget,pSelector);
    CCHttpClient::getInstance()->send(request);
}