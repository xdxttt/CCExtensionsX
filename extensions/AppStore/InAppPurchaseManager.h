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

- (void) restorePurchase;

- (void) requestSKProducts:(NSSet *)productIds;

- (void) purchase:(NSString *)productId Quantity:(NSInteger)quantity;

- (void) completeTransaction:(NSString *)transactionIdentifier;

@property (nonatomic, assign) NSArray *products;

@end
#endif /* defined(__InAppPurchaseManager__) */
