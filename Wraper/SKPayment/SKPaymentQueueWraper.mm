//
//  CCIAP.cpp
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-4-26.
//
//

#include "SKPaymentQueueWraper.h"
#include "SKPaymentTransactionObserverImp.h"
SKPaymentQueueWraper *s_SKPaymentQueueWraper = NULL;
SKPaymentTransactionObserverImp *s_SKPaymentTransactionObserverImp = NULL;
SKPaymentQueueListener* s_SKPaymentQueueListener = NULL;

SKPaymentQueueWraper::SKPaymentQueueWraper(){
}
SKPaymentQueueWraper::~SKPaymentQueueWraper(){
}
void SKPaymentQueueWraper::destroyInstance()
{
    if (s_SKPaymentQueueWraper) {
        delete s_SKPaymentQueueWraper;
    }
    if (s_SKPaymentTransactionObserverImp) {
        [s_SKPaymentTransactionObserverImp release];
    }
}

SKPaymentQueueWraper* SKPaymentQueueWraper::getInstance()
{
    if (s_SKPaymentQueueWraper == NULL) {
        s_SKPaymentQueueWraper = new SKPaymentQueueWraper();
    }
    if (s_SKPaymentTransactionObserverImp == NULL) {
        s_SKPaymentTransactionObserverImp = [SKPaymentTransactionObserverImp alloc];
    }
    return s_SKPaymentQueueWraper;
}
void SKPaymentQueueWraper::purchase(SKPaymentQueueListener* listener,std::string products_id,int quantity){
    s_SKPaymentQueueListener = listener;
    NSString *pid = [[[NSString alloc] initWithCString:products_id.c_str() encoding:NSUTF8StringEncoding] autorelease];
    [s_SKPaymentTransactionObserverImp purchase:pid Quantity:quantity];
}
void SKPaymentQueueWraper::restorePurchase(SKPaymentQueueListener* listener){
    s_SKPaymentQueueListener = listener;
    [s_SKPaymentTransactionObserverImp restorePurchase];
}

void SKPaymentQueueWraper::completeTransaction(std::string transactionIdentifier){
     NSString*strtid = [[NSString alloc] initWithCString:transactionIdentifier.c_str() encoding:NSUTF8StringEncoding];
    [s_SKPaymentTransactionObserverImp completeTransaction:strtid];
}

