//
//  CCIAP.cpp
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-4-26.
//
//

#include "SKProductsRequestWraper.h"
#include "HttpClient.h"
#include "Crypto.h"
#include "SKProductsRequestDelegateImp.h"

#include "LoadingHelper.h"
SKProductsRequestWraper *s_SKProductsRequestWraper = NULL;
SKProductsRequestDelegateImp *s_SKProductsRequestDelegateImp = NULL;
RequestSKProductsCallback s_RequestSKProductsCallback = NULL;

SKProductsRequestWraper::SKProductsRequestWraper(){
}
SKProductsRequestWraper::~SKProductsRequestWraper(){
}
void SKProductsRequestWraper::destroyInstance()
{
    if (s_SKProductsRequestWraper) {
        s_SKProductsRequestWraper->release();
    }
    if (s_SKProductsRequestDelegateImp) {
        [s_SKProductsRequestDelegateImp release];
    }
}

SKProductsRequestWraper* SKProductsRequestWraper::getInstance()
{
    if (s_SKProductsRequestWraper == NULL) {
        s_SKProductsRequestWraper = new SKProductsRequestWraper();
    }
    if (s_SKProductsRequestDelegateImp == NULL) {
        s_SKProductsRequestDelegateImp = [SKProductsRequestDelegateImp alloc];
    }
    return s_SKProductsRequestWraper;
}
void SKProductsRequestWraper::requestSKProducts(std::list<std::string> products_ids,const RequestSKProductsCallback &cb){

    NSMutableArray *mutablearray = [[NSMutableArray alloc] initWithCapacity:products_ids.size()];
    for (std::list<std::string>::iterator iter = products_ids.begin(); iter!=products_ids.end(); iter++) {
        NSString*products_id = [[NSString alloc] initWithCString:(*iter).c_str() encoding:NSUTF8StringEncoding];
        [mutablearray addObject:products_id];
    }
    NSSet *productIdentifiers  = [[NSSet alloc] initWithArray:mutablearray];
    s_RequestSKProductsCallback = cb;
    [s_SKProductsRequestDelegateImp requestSKProducts:productIdentifiers];
}

