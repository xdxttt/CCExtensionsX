#import "SKProductsRequestDelegateImp.h"
#include "SKProductsRequestWraper.h"
#import "SKPaymentTransactionObserverImp.h"
extern SKPaymentTransactionObserverImp *s_SKPaymentTransactionObserverImp;
extern SKProductsRequestListener *s_SKProductsRequestListener;

@implementation SKProductsRequestDelegateImp
#pragma mark -
#pragma mark SKProductsRequestDelegate methods
- (void) requestSKProducts:(NSSet *)productIds
{
    SKProductsRequest* productsRequest = [[SKProductsRequest alloc]initWithProductIdentifiers:productIds];
    [productsRequest setDelegate:self];
    [productsRequest start];
}
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    if(!s_SKPaymentTransactionObserverImp){
        s_SKPaymentTransactionObserverImp = [SKPaymentTransactionObserverImp alloc];
    }
    s_SKPaymentTransactionObserverImp.products = response.products;
    [s_SKPaymentTransactionObserverImp.products retain];
    std::list<SKProductWraper*> list;
    for (int index = 0; index < [response.products count]; index++) {
        SKProduct *skProduct = [response.products objectAtIndex:index];
        SKProductWraper*item = new SKProductWraper;
        item->localizedDescription = [skProduct.localizedDescription UTF8String];
        item->localizedTitle = [skProduct.localizedTitle UTF8String];
        item->productIdentifier = [skProduct.productIdentifier UTF8String];
        item->localizedDescription = [skProduct.localizedDescription UTF8String];
        item->price = [skProduct.price doubleValue];
        
        NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
        [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
        [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
        [numberFormatter setLocale:skProduct.priceLocale];
        NSString *formattedPrice = [numberFormatter stringFromNumber:skProduct.price];
        item->priceLocale = [formattedPrice UTF8String];
        
        list.push_back(item);
    }
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
        NSLog(@"Invalid product id: %@" , invalidProductId);
    }
    if(s_SKProductsRequestListener){
       s_SKProductsRequestListener->RequestSKProductsCallback(list);
    }
    for (std::list<SKProductWraper*>::iterator iter = list.begin(); iter!=list.end(); iter++) {
        delete *iter;
    }
}
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    NSLog(@"didFailWithError:%@" , error);
    std::list<SKProductWraper*> list;
    if(s_SKProductsRequestListener){
        s_SKProductsRequestListener->RequestSKProductsCallback(list);
    }
}
@end

