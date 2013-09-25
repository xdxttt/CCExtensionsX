//
//  CCIAP.cpp
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-4-26.
//
//

#include "APPStoreIAP.h"
#include "HttpClient.h"
#include "curl/curl.h"
#include "Crypto.h"

using namespace cocos2d::extension;

#include "InAppPurchaseManager.h"
CCAppStoreIAP *s_CCIAP = NULL;
InAppPurchaseManager *s_iapManager = NULL;


CCAppStoreIAPContent * s_requestSKProductsContent;
CCAppStoreIAPContent * s_payContent;

std::map<void*,CCAppStoreIAPContent*> notify_content;


CCAppStoreIAP::CCAppStoreIAP(){
}
CCAppStoreIAP::~CCAppStoreIAP(){
}
void CCAppStoreIAP::destroyInstance()
{
    if (s_CCIAP) {
        s_CCIAP->release();
      
    }
    if (s_iapManager) {
        [s_iapManager release];
    }
}

CCAppStoreIAP* CCAppStoreIAP::getInstance()
{
    if (s_CCIAP == NULL) {
        s_CCIAP = new CCAppStoreIAP();
    }
    if (s_iapManager == NULL) {
        s_iapManager = [InAppPurchaseManager alloc];
    }
    return s_CCIAP;
}
int CCAppStoreIAP::requestSKProducts(std::list<std::string> products_ids,CCObject* pTarget, SEL_CallFuncND pSelector){
    if (s_requestSKProductsContent ==NULL) {
        s_requestSKProductsContent = new CCAppStoreIAPContent;
        s_requestSKProductsContent->pTarget = pTarget;
        s_requestSKProductsContent->pSelector = pSelector;
    }else{
        return 1;
    }
    
    NSMutableArray *mutablearray = [[NSMutableArray alloc] initWithCapacity:products_ids.size()];
    for (std::list<std::string>::iterator iter = products_ids.begin(); iter!=products_ids.end(); iter++) {
        NSString*products_id = [[NSString alloc] initWithCString:(*iter).c_str() encoding:NSUTF8StringEncoding];
        [mutablearray addObject:products_id];
    }
    NSSet *productIdentifiers  = [[NSSet alloc] initWithArray:mutablearray];
    [s_iapManager requestSKProducts:productIdentifiers];
    return 0;
}

int CCAppStoreIAP::pay(std::string products_id,int quantity,CCObject* pTarget, SEL_CallFuncND pSelector){

    if (s_payContent ==NULL) {
        s_payContent = new CCAppStoreIAPContent;
        s_payContent->pTarget = pTarget;
        s_payContent->pSelector = pSelector;
    }

    NSString *pid = [[NSString alloc] initWithCString:products_id.c_str() encoding:NSUTF8StringEncoding];
    [s_iapManager pay:pid Quantity:quantity];

    return 0;
}

void CCAppStoreIAP::setupServiceAddress(const char* address){
    this->address = address;
}

void CCAppStoreIAP::setupSecretKey(const char *secretKey){
    this->secretKey = secretKey;
}
void CCAppStoreIAP::setupAppID(const char *appID){
    this->appID = appID;
}

int CCAppStoreIAP::verify(const char* businessID, std::string productIdentifier,std::string receipt,CCObject* pTarget, SEL_CallFuncND pSelector){
    CCHttpRequest *request = new CCHttpRequest ;
    std::string url;
    url.append(address);
    url.append("/serviceiap/iapVerify");
    url.append(appID);
    url.append("/");
    url.append(businessID);
    
    std::string post;
    CURL *easy_handle = curl_easy_init();
    char *base64data = curl_easy_escape(easy_handle, receipt.c_str(), receipt.length());
    post.append("receipt=").append(base64data);
    curl_easy_cleanup(easy_handle);
    request->setUrl(url.c_str());
    
    url.append(secretKey).c_str();
    std::string sign = CCCrypto::getInstance()->md5(url.c_str(),url.length());
    
    post.append("&sign=").append(sign);
    
    request->setRequestType(CCHttpRequest::kHttpPost);

    request->setRequestData(post.c_str(), post.length());
    request->setResponseCallback(pTarget, pSelector);
    
    CCHttpClient::getInstance()->send(request);
    return 0;
}
int CCAppStoreIAP::completeTransaction(std::string transactionIdentifier){
 
    NSString*strtid = [[NSString alloc] initWithCString:transactionIdentifier.c_str() encoding:NSUTF8StringEncoding];
    [s_iapManager completeTransaction:strtid];
    return 0;
}

