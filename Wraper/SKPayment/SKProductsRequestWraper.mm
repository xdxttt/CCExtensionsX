#include "SKProductsRequestWraper.h"
#include "SKProductsRequestDelegateImp.h"
SKProductsRequestWraper *s_SKProductsRequestWraper = NULL;
SKProductsRequestDelegateImp *s_SKProductsRequestDelegateImp = NULL;
SKProductsRequestListener *s_SKProductsRequestListener = NULL;

SKProductsRequestWraper::SKProductsRequestWraper(){
}
SKProductsRequestWraper::~SKProductsRequestWraper(){
}
void SKProductsRequestWraper::destroyInstance()
{
    if (s_SKProductsRequestWraper) {
       delete s_SKProductsRequestWraper;
    }
    if (s_SKProductsRequestDelegateImp) {
        [s_SKProductsRequestDelegateImp release];
    }
}

SKProductsRequestWraper* SKProductsRequestWraper::getInstance()
{
    if (s_SKProductsRequestWraper == NULL) {
        s_SKProductsRequestWraper = new SKProductsRequestWraper();
    }
    if (s_SKProductsRequestDelegateImp == NULL) {
        s_SKProductsRequestDelegateImp = [SKProductsRequestDelegateImp alloc];
    }
    return s_SKProductsRequestWraper;
}
void SKProductsRequestWraper::requestSKProducts(SKProductsRequestListener *listener,std::list<std::string> products_ids){
    s_SKProductsRequestListener = listener;
    NSMutableArray *mutablearray = [[NSMutableArray alloc] initWithCapacity:products_ids.size()];
    for (std::list<std::string>::iterator iter = products_ids.begin(); iter!=products_ids.end(); iter++) {
        NSString*products_id = [[NSString alloc] initWithCString:(*iter).c_str() encoding:NSUTF8StringEncoding];
        [mutablearray addObject:products_id];
    }
    NSSet *productIdentifiers  = [[NSSet alloc] initWithArray:mutablearray];
    [s_SKProductsRequestDelegateImp requestSKProducts:productIdentifiers];
}

