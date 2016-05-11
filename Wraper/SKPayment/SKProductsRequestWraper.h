#pragma once
#include <list>
#include <string>
class SKProductWraper {
public:
    SKProductWraper(){}
~SKProductWraper(){}
    std::string localizedDescription;
    std::string localizedTitle;
    std::string priceLocale;
    std::string localeCurrencyCode;
    double price;
    std::string productIdentifier;
};

class SKProductsRequestListener{
public:
    SKProductsRequestListener(){};
    virtual ~SKProductsRequestListener(){};
    virtual void RequestSKProductsCallback(std::list<SKProductWraper*> products) = 0;
};

class SKProductsRequestWraper{
public:
    static SKProductsRequestWraper *getInstance();
    static void destroyInstance();
public:
    SKProductsRequestWraper();
    ~SKProductsRequestWraper();
    void requestSKProducts(SKProductsRequestListener *listener,std::list<std::string> products_ids);
    void cancel();
private:
};
