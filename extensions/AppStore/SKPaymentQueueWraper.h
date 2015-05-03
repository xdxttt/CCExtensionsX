#pragma once
#include "cocos2d.h"
#include <list>
using namespace cocos2d;
enum {
    AppStorePaymentTransactionStatePurchasing,    // Transaction is being added to the server queue.
    AppStorePaymentTransactionStatePurchased,     // Transaction is in queue, user has been charged.  Client should complete the transaction.
    AppStorePaymentTransactionStateFailed,        // Transaction was cancelled or failed before being added to the server queue.
    AppStorePaymentTransactionStateRestored       // Transaction was restored from user's purchase history.  Client should complete the transaction.
};

class SKPaymentWraper {
public:
    SKPaymentWraper(){
        requestData = NULL;
    }
    ~SKPaymentWraper(){}
    std::string productIdentifier;
    unsigned char* requestData;
    long quantity;
};

class SKPaymentTransactionWraper {
public:
    SKPaymentTransactionWraper(){
        transactionReceipt = NULL;
        transactionDate = NULL;
    }
    ~SKPaymentTransactionWraper(){}
    
    int transactionState;
    
    std::string transactionIdentifier;
   
    unsigned char* transactionDate;
    
    char* transactionReceipt;

    std::string error;
  
    SKPaymentWraper payment;
    
    //NSArray *downloads;
};
//class AppStoreReceipt{
//    AppStoreReceipt(){
//        
//    }
//    ~AppStoreReceipt(){}
//    std::string original_purchase_date_pst;
//    int purchase_date_ms;
//    std::string unique_identifier;
//    std::string original_transaction_id;
//    std::string bvrs;
//    std::string transaction_id;
//    int quantity;
//    int item_id;
//    std::string product_id;
//    std::string purchase_date;
//    std::string purchase_date_pst;
//    int original_purchase_date_ms;
//    std::string bid;
//};

class AppStorePurchaseContent {
    AppStorePurchaseContent(){
     }
    ~AppStorePurchaseContent(){}
};

typedef std::function<void(std::list<SKPaymentTransactionWraper*> appStorePaymentTransactions)> UpdatedTransactionsCallBack;
class SKPaymentQueueWraper :public cocos2d::Ref{
public:
    static SKPaymentQueueWraper *getInstance();
    static void destroyInstance();
public:
    SKPaymentQueueWraper();
    ~SKPaymentQueueWraper();
    void purchase(std::string products_id,int quantity,const UpdatedTransactionsCallBack &cb);
    void restorePurchase(const UpdatedTransactionsCallBack &cb);
    void completeTransaction(std::string transactionIdentifier);
};
