//
//  InAppPurchaseManager.m
//
//  Created by xudexin on 13-4-23.
//
//

#import "SKPaymentTransactionObserverImp.h"
#include "SKPaymentQueueWraper.h"

extern UpdatedTransactionsCallBack s_UpdatedTransactionsCallBack;
@implementation SKPaymentTransactionObserverImp
#pragma mark -
#pragma mark SKPaymentTransactionObserver methods

- (BOOL) canMakePayments
{
    return [SKPaymentQueue canMakePayments];
}
- (void)restorePurchase{
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
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
    std::list<SKPaymentTransactionWraper*> list;
    for (SKPaymentTransaction* transaction in transactions)
    {
        SKPaymentTransactionWraper* item = new SKPaymentTransactionWraper;
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
    if(s_UpdatedTransactionsCallBack){
        s_UpdatedTransactionsCallBack(list);
    }
    for (std::list<SKPaymentTransactionWraper*>::iterator iter = list.begin(); iter!=list.end(); iter++) {
        delete *iter;
    }
}

@end

