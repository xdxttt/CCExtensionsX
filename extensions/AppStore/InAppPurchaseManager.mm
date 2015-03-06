//
//  InAppPurchaseManager.m
//
//  Created by xudexin on 13-4-23.
//
//

#import "InAppPurchaseManager.h"
#include "APPStoreIAP.h"

extern AppStoreIAPContent * s_requestSKProductsContent;
extern AppStoreIAPContent * s_purchaseContent;
@implementation InAppPurchaseManager
#pragma mark -
#pragma mark SKProductsRequestDelegate methods

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
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    _products = [response.products retain];
    std::list<AppStoreProducts*> list;
    for (int index = 0; index < [response.products count]; index++) {
        SKProduct *skProduct = [response.products objectAtIndex:index];
        AppStoreProducts*item = new AppStoreProducts;
        item->localizedDescription = [skProduct.localizedDescription UTF8String];
        item->localizedTitle = [skProduct.localizedTitle UTF8String];
        item->productIdentifier = [skProduct.productIdentifier UTF8String];
        item->localizedDescription = [skProduct.localizedDescription UTF8String];
        item->price = [skProduct.price doubleValue];
        list.push_back(item);
    }
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
        NSLog(@"Invalid product id: %@" , invalidProductId);
    }
    if(s_requestSKProductsContent){
        Ref *pTarget = s_requestSKProductsContent->pTarget;
        SEL_CallFuncND pSelector =s_requestSKProductsContent->pSelector;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(NULL,&list);
        }
        delete s_requestSKProductsContent;
        s_requestSKProductsContent = NULL;
    }
    for (std::list<AppStoreProducts*>::iterator iter = list.begin(); iter!=list.end(); iter++) {
        delete *iter;
    }
}
- (void) completeTransaction:(NSString *)transactionIdentifier
{
    for (SKPaymentTransaction* transaction in [[SKPaymentQueue defaultQueue] transactions])
    {
      if (transaction.transactionState == SKPaymentTransactionStatePurchased || transaction.transactionState == SKPaymentTransactionStateRestored)
       {
            if ([transactionIdentifier compare:transaction.transactionIdentifier] == NSOrderedSame)
            {
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                return;
            }
       }
    }
}

- (void) purchase:(NSString *)productId Quantity:(NSInteger)quantity
{
    SKProduct *product = NULL;
    for (int index = 0; index < [_products count]; index++) {
        SKProduct *item = _products[index];
        if ([productId compare:item.productIdentifier] == NSOrderedSame){
            product = item;
        }
    }
    SKMutablePayment* payment = [SKMutablePayment paymentWithProduct:product];
    [payment setQuantity:quantity];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
}
- (void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    std::list<AppStorePaymentTransaction*> list;
    for (SKPaymentTransaction* transaction in transactions)
    {
        AppStorePaymentTransaction* item = new AppStorePaymentTransaction;
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
    if(s_purchaseContent){
        Ref *pTarget = s_purchaseContent->pTarget;
        SEL_CallFuncND pSelector =s_purchaseContent->pSelector;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(NULL,&list);
        }
    }
    
    for (std::list<AppStorePaymentTransaction*>::iterator iter = list.begin(); iter!=list.end(); iter++) {
        delete *iter;
    }
}

@end

