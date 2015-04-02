//
//  CCIAP.cpp
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-4-26.
//
//

#include "APPStoreIAP.h"
#include "HttpClient.h"
#include "Crypto.h"
#include "InAppPurchaseManager.h"
#include "LoadingHelper.h"
AppStoreIAP *s_CCIAP = NULL;
InAppPurchaseManager *s_iapManager = NULL;
AppStoreIAPContent * s_requestSKProductsContent;
AppStoreIAPContent * s_purchaseContent;

std::map<void*,AppStoreIAPContent*> notify_content;


AppStoreIAP::AppStoreIAP(){
}
AppStoreIAP::~AppStoreIAP(){
}
void AppStoreIAP::destroyInstance()
{
    if (s_CCIAP) {
        s_CCIAP->release();
      
    }
    if (s_iapManager) {
        [s_iapManager release];
    }
}

AppStoreIAP* AppStoreIAP::getInstance()
{
    if (s_CCIAP == NULL) {
        s_CCIAP = new AppStoreIAP();
    }
    if (s_iapManager == NULL) {
        s_iapManager = [InAppPurchaseManager alloc];
    }
    return s_CCIAP;
}
void AppStoreIAP::requestSKProducts(std::list<std::string> products_ids,Ref* pTarget, SEL_CallFuncND pSelector){

    NSMutableArray *mutablearray = [[NSMutableArray alloc] initWithCapacity:products_ids.size()];
    for (std::list<std::string>::iterator iter = products_ids.begin(); iter!=products_ids.end(); iter++) {
        NSString*products_id = [[NSString alloc] initWithCString:(*iter).c_str() encoding:NSUTF8StringEncoding];
        [mutablearray addObject:products_id];
    }
    NSSet *productIdentifiers  = [[NSSet alloc] initWithArray:mutablearray];
    
    if (s_requestSKProductsContent ==NULL) {
        s_requestSKProductsContent = new AppStoreIAPContent;
        s_requestSKProductsContent->pTarget = pTarget;
        s_requestSKProductsContent->pSelector = pSelector;
    }
    [s_iapManager requestSKProducts:productIdentifiers];
}

void AppStoreIAP::purchase(std::string products_id,int quantity,Ref* pTarget, SEL_CallFuncND pSelector){
    if (s_purchaseContent ==NULL) {
        s_purchaseContent = new AppStoreIAPContent;
        s_purchaseContent->pTarget = pTarget;
        s_purchaseContent->pSelector = pSelector;
    }
    NSString *pid = [[NSString alloc] initWithCString:products_id.c_str() encoding:NSUTF8StringEncoding];
    [s_iapManager purchase:pid Quantity:quantity];
}
void AppStoreIAP::restorePurchase(Ref* pTarget, SEL_CallFuncND pSelector){
    if (s_purchaseContent ==NULL) {
        s_purchaseContent = new AppStoreIAPContent;
        s_purchaseContent->pTarget = pTarget;
        s_purchaseContent->pSelector = pSelector;
    }
    [s_iapManager restorePurchase];
}


void AppStoreIAP::completeTransaction(std::string transactionIdentifier){
     NSString*strtid = [[NSString alloc] initWithCString:transactionIdentifier.c_str() encoding:NSUTF8StringEncoding];
    [s_iapManager completeTransaction:strtid];
}

