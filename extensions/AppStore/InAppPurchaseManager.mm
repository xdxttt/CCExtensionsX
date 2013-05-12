//
//  InAppPurchaseManager.m
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-4-23.
//
//

#import "InAppPurchaseManager.h"
#include "APPStoreIAP.h"

extern CCAppStoreIAPContent * s_requestSKProductsContent;
extern CCAppStoreIAPContent * s_payContent;
@implementation InAppPurchaseManager
#pragma mark -
#pragma mark SKProductsRequestDelegate methods
//NSSet *productIdentifiers = [NSSet setWithObject:@"test_1_0.99" ];

- (void) requestSKProducts:(NSSet *)productId
{
    SKProductsRequest* productsRequest = [[SKProductsRequest alloc]initWithProductIdentifiers:productId];
    [productsRequest setDelegate:self];
    [productsRequest start];
}
- (BOOL) canMakePayments
{
    return [SKPaymentQueue canMakePayments];
}
- (void) needServerVerify:(BOOL)isNeed
{
    needServerVerify = isNeed;
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    std::list<CCAppStoreProducts*> list;
    printf("didReceiveResponse:%s",[response.debugDescription UTF8String]);
    printf("didReceiveResponse:%s",[response.description UTF8String]);
    
    for(SKProduct *product in response.products)
    {
        NSLog(@"Product title: %@" , product.localizedTitle);
        NSLog(@"Product description: %@" , product.localizedDescription);
        NSLog(@"Product price: %@" , product.price);
        NSLog(@"Product id: %@" , product.productIdentifier);
        CCAppStoreProducts*item = new CCAppStoreProducts;
        item->localizedDescription = [product.localizedDescription UTF8String];
        item->localizedTitle = [product.localizedTitle UTF8String];
        item->productIdentifier = [product.productIdentifier UTF8String];
        item->localizedDescription = [product.localizedDescription UTF8String];
        item->price = [product.price doubleValue];
        list.push_back(item);
    }
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
        NSLog(@"Invalid product id: %@" , invalidProductId);
    }
    if(s_requestSKProductsContent){
        
        CCObject *pTarget = s_requestSKProductsContent->pTarget;
        SEL_CallFuncND pSelector =s_requestSKProductsContent->pSelector;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(NULL,&list);
        }
        delete s_requestSKProductsContent;
        s_requestSKProductsContent = NULL;
    }
    for (std::list<CCAppStoreProducts*>::iterator iter = list.begin(); iter!=list.end(); iter++) {
        delete *iter;
    }
}
- (void) completeTransaction:(NSString *)transactionIdentifier
{
    for (SKPaymentTransaction* transaction in [[SKPaymentQueue defaultQueue] transactions])
    {
       // if (transaction.transactionState == SKPaymentTransactionStatePurchased || transaction.transactionState == SKPaymentTransactionStateRestored)
        //{
            if ([transactionIdentifier compare:transaction.transactionIdentifier] == NSOrderedSame)
            {
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                return;
            }
       // }
    }
}
/*
 - (void) completeTransaction:(SKPaymentTransaction*)transaction
 {
 [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
 }
 */
//购买物品
- (void) pay:(NSString *)payId Quantity:(NSInteger)quantity
{
    SKMutablePayment* payment = [SKMutablePayment paymentWithProductIdentifier:payId];
    [payment setQuantity:quantity];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    
}
- (void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    std::list<CCAppStorePaymentTransaction*> list;
    for (SKPaymentTransaction* transaction in transactions)
    {
        CCAppStorePaymentTransaction* item = new CCAppStorePaymentTransaction;
        item->transactionState = transaction.transactionState;
        if (transaction.transactionIdentifier) {
            item->transactionIdentifier = [transaction.transactionIdentifier UTF8String];
        }
        if (transaction.transactionDate) {
            // NSString* temp = [[NSString alloc] initWithData:transaction.transactionDate   encoding:NSASCIIStringEncoding];
            // item->transactionDate = (unsigned char *)[transaction.transactionDate bytes];
        }
        if (transaction.transactionReceipt) {
            NSString* receipt = [[NSString alloc] initWithData:[transaction transactionReceipt] encoding:NSUTF8StringEncoding];
            
            item->transactionReceipt = (char *)[receipt UTF8String];
        }
        item->payment.productIdentifier = [transaction.payment.productIdentifier UTF8String];
        if (transaction.payment.requestData) {
            item->payment.requestData = (unsigned char *)[transaction.payment.requestData bytes];
        }
        item->payment.quantity = transaction.payment.quantity;
        if (transaction.error) {
            item->error = [[transaction.error description] UTF8String];
        }
        list.push_back(item);
    }
    if(s_payContent){
        
        CCObject *pTarget = s_payContent->pTarget;
        SEL_CallFuncND pSelector =s_payContent->pSelector;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(NULL,&list);
        }
    }
    
    for (std::list<CCAppStorePaymentTransaction*>::iterator iter = list.begin(); iter!=list.end(); iter++) {
        delete *iter;
    }
}

@end

