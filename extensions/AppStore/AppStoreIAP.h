//
//  AppStoreIAP.h
//
//

#ifndef __AppStoreIAP__
#define __AppStoreIAP__
#include "cocos2d.h"
#include <list>
using namespace cocos2d;

class AppStoreIAPContent {
public:
    AppStoreIAPContent(){
        pTarget = NULL;
        pSelector = NULL;
    }
    ~AppStoreIAPContent(){
        
    }
    Ref* pTarget;
    SEL_CallFuncND pSelector;
};


class AppStoreProducts {
public:
    AppStoreProducts(){}
    ~AppStoreProducts(){}
    
    std::string localizedDescription;
    
    std::string localizedTitle;
    
    std::string priceLocale;
    
    double price;
    
    std::string productIdentifier;
    
};

enum {
    AppStorePaymentTransactionStatePurchasing,    // Transaction is being added to the server queue.
    AppStorePaymentTransactionStatePurchased,     // Transaction is in queue, user has been charged.  Client should complete the transaction.
    AppStorePaymentTransactionStateFailed,        // Transaction was cancelled or failed before being added to the server queue.
    AppStorePaymentTransactionStateRestored       // Transaction was restored from user's purchase history.  Client should complete the transaction.
};

class AppStorePayment {
public:
    AppStorePayment(){
        requestData = NULL;
    }
    ~AppStorePayment(){}
    
    std::string productIdentifier;
    
    unsigned char* requestData;
    
    long quantity;
};
class AppStorePaymentTransaction {
public:
    AppStorePaymentTransaction(){
        transactionReceipt = NULL;
        transactionDate = NULL;
    }
    ~AppStorePaymentTransaction(){}
    
    int transactionState;
    
    std::string transactionIdentifier;
   
    unsigned char* transactionDate;
    
    char* transactionReceipt;

    std::string error;
  
    AppStorePayment payment;
    
    //NSArray *downloads;
};
class AppStoreReceipt{
    AppStoreReceipt(){
        
    }
    ~AppStoreReceipt(){}
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

class AppStorePurchaseContent {
    AppStorePurchaseContent(){
 
    }
    ~AppStorePurchaseContent(){}
};


class AppStoreIAP :public cocos2d::Ref{
public:
    static AppStoreIAP *getInstance();
    static void destroyInstance();
public:
    AppStoreIAP();
    ~AppStoreIAP();
    //  std::list<AppStoreProducts*>* list =(std::list<AppStoreProducts*>*)data;
    void requestSKProducts(std::list<std::string> products_ids,Ref* pTarget, SEL_CallFuncND pSelector);
    //  std::list<AppStorePaymentTransaction*>* list =(std::list<AppStorePaymentTransaction*>*)data;
    void purchase(std::string products_id,int quantity,Ref* pTarget, SEL_CallFuncND pSelector);
   
    void completeTransaction(std::string transactionIdentifier);
private:
    std::string address;
    std::string secretKey;
    std::string appID;
};
#endif /* defined(__AppStoreIAP__) */
