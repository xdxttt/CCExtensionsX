#pragma once
#include "cocos2d.h"
#include <list>
using namespace cocos2d;

class SKProductWraper {
public:
    SKProductWraper(){}
~SKProductWraper(){}
    std::string localizedDescription;
    std::string localizedTitle;
    std::string priceLocale;
    double price;
    std::string productIdentifier;
};
typedef std::function<void(std::list<SKProductWraper*> products)> RequestSKProductsCallback;

class SKProductsRequestWraper :public cocos2d::Ref{
public:
    static SKProductsRequestWraper *getInstance();
    static void destroyInstance();
public:
    SKProductsRequestWraper();
    ~SKProductsRequestWraper();
    void requestSKProducts(std::list<std::string> products_ids,const RequestSKProductsCallback &cb);
private:
};
