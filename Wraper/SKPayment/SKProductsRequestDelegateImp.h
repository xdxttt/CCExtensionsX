#pragma once
#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@interface SKProductsRequestDelegateImp : NSObject <SKProductsRequestDelegate>
{
}
- (void) requestSKProducts:(NSSet *)productIds;
@end
