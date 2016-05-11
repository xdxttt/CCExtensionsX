#import "SKPaymentTransactionObserverImp.h"
#include "SKPaymentQueueWraper.h"
extern SKPaymentTransactionObserverImp *s_SKPaymentTransactionObserverImp;
extern SKPaymentQueueListener* s_SKPaymentQueueListener;
@implementation SKPaymentTransactionObserverImp
#pragma mark -
#pragma mark SKPaymentTransactionObserver methods

- (BOOL) canMakePayments
{
    return [SKPaymentQueue canMakePayments];
}
- (void)restorePurchase{
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
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
    if (product) {
        SKMutablePayment* payment = [SKMutablePayment paymentWithProduct:product];
        [payment setQuantity:quantity];
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        [[SKPaymentQueue defaultQueue] addPayment:payment];
    }
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
    if(s_SKPaymentQueueListener){
        s_SKPaymentQueueListener->UpdatedTransactionsCallBack(list);
    }
    for (std::list<SKPaymentTransactionWraper*>::iterator iter = list.begin(); iter!=list.end(); iter++) {
        delete *iter;
    }
}

// Sent when transactions are removed from the queue (via finishTransaction:).
- (void) paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray <SKPaymentTransaction *> *)transactions{
    NSLog(@"removedTransactions");

}

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void) paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error{
    NSLog(@"restoreCompletedTransactionsFailedWithError");
}

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void) paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue{
    NSLog(@"paymentQueueRestoreCompletedTransactionsFinished");
    std::list<SKPaymentTransactionWraper*> list;
    for (SKPaymentTransaction* transaction in [SKPaymentQueue defaultQueue].transactions)
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
    if(s_SKPaymentQueueListener){
        s_SKPaymentQueueListener->UpdatedTransactionsCallBack(list);
    }
    for (std::list<SKPaymentTransactionWraper*>::iterator iter = list.begin(); iter!=list.end(); iter++) {
        delete *iter;
    }
}

// Sent when the download state has changed.
- (void) paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray <SKDownload *> *)downloads{
      NSLog(@"updatedDownloads");
}

@end

