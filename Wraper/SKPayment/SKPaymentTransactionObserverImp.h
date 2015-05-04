#pragma once
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import <StoreKit/SKPaymentTransaction.h>

@interface SKPaymentTransactionObserverImp : NSObject <SKPaymentTransactionObserver>
{
}
- (BOOL) canMakePayments;

- (void) restorePurchase;

- (void) purchase:(NSString *)productId Quantity:(NSInteger)quantity;

- (void) completeTransaction:(NSString *)transactionIdentifier;

@property (nonatomic, assign) NSArray *products;

@end
