//
//  InAppPurchaseManager.h
//
//  Created by xudexin on 13-4-23.
//
//

#ifndef __InAppPurchaseManager__
#define __InAppPurchaseManager__

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import <StoreKit/SKPaymentTransaction.h>

@interface InAppPurchaseManager : NSObject <SKPaymentTransactionObserver,SKProductsRequestDelegate>
{
    BOOL needServerVerify;
}
- (BOOL) canMakePayments;

- (void) needServerVerify:(BOOL)isNeed;

- (void) requestSKProducts:(NSSet *)productId;

- (void) pay:(NSString *)productId Quantity:(NSInteger)quantity;
- (void) completeTransaction:(NSString *)transactionIdentifier;

@end
#endif /* defined(__InAppPurchaseManager__) */
