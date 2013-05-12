//
//  CCAppStoreIAP.h
//
//

#ifndef __CCAppStoreIAP__
#define __CCAppStoreIAP__
#include "cocos2d.h"
#include <list>
using namespace cocos2d;

class CCAppStoreIAPContent {
public:
    CCAppStoreIAPContent(){
        pTarget = NULL;
        pSelector = NULL;
    }
    ~CCAppStoreIAPContent(){
        
    }
    CCObject* pTarget;
    
    SEL_CallFuncND pSelector;
};


class CCAppStoreProducts {
public:
    CCAppStoreProducts(){}
    ~CCAppStoreProducts(){}
    
    std::string localizedDescription;
    
    std::string localizedTitle;
    
    std::string priceLocale;
    
    double price;
    
    std::string productIdentifier;
};

enum {
    CCAppStorePaymentTransactionStatePurchasing,    // Transaction is being added to the server queue.
    CCAppStorePaymentTransactionStatePurchased,     // Transaction is in queue, user has been charged.  Client should complete the transaction.
    CCAppStorePaymentTransactionStateFailed,        // Transaction was cancelled or failed before being added to the server queue.
    CCAppStorePaymentTransactionStateRestored       // Transaction was restored from user's purchase history.  Client should complete the transaction.
};

class CCAppStorePayment {
public:
    CCAppStorePayment(){
        requestData = NULL;
    }
    ~CCAppStorePayment(){}
    
    std::string productIdentifier;
    
    unsigned char* requestData;
    
    int quantity;
};
class CCAppStorePaymentTransaction {
public:
    CCAppStorePaymentTransaction(){
        transactionReceipt = NULL;
        transactionDate = NULL;
    }
    ~CCAppStorePaymentTransaction(){}
    
    int transactionState;
    
    std::string transactionIdentifier;
   
    unsigned char* transactionDate;
    
    char* transactionReceipt;

    std::string error;
  
    CCAppStorePayment payment;
    
    //NSArray *downloads;
};
class CCAppStoreReceipt{
    CCAppStoreReceipt(){
        
    }
    ~CCAppStoreReceipt(){}
    std::string original_purchase_date_pst;
    int purchase_date_ms;
    std::string unique_identifier;
    std::string original_transaction_id;
    std::string bvrs;
    std::string transaction_id;
    int quantity;
    int item_id;
    std::string product_id;
    std::string purchase_date;
    std::string purchase_date_pst;
    int original_purchase_date_ms;
    std::string bid;
};

class CCAppStorePurchaseContent {
    CCAppStorePurchaseContent(){
 
    }
    ~CCAppStorePurchaseContent(){}
};


class CCAppStoreIAP :public cocos2d::CCObject{
public:
    static CCAppStoreIAP *getInstance();
    static void destroyInstance();
public:
    CCAppStoreIAP();
    ~CCAppStoreIAP();

    void setupServiceAddress(const char* address);
    void setupServiceToken(const char* token);
    
    int requestSKProducts(std::list<std::string> products_ids,CCObject* pTarget, SEL_CallFuncND pSelector);
    
    int pay(std::string products_id,int quantity,CCObject* pTarget, SEL_CallFuncND pSelector);
    
    int verify(const char* businessID, std::string productIdentifier,std::string receipt,CCObject* pTarget, SEL_CallFuncND pSelector);
    
    int completeTransaction(std::string transactionIdentifier);
private:
    std::string address;
    std::string token;
};
#endif /* defined(__CCAppStoreIAP__) */
