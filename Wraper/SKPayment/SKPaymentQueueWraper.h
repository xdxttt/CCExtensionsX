#pragma once
#include <list>
#include <string>
enum {
    AppStorePaymentTransactionStatePurchasing,    // Transaction is being added to the server queue.
    AppStorePaymentTransactionStatePurchased,     // Transaction is in queue, user has been charged.  Client should complete the transaction.
    AppStorePaymentTransactionStateFailed,        // Transaction was cancelled or failed before being added to the server queue.
    AppStorePaymentTransactionStateRestored       // Transaction was restored from user's purchase history.  Client should complete the
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

class SKPaymentQueueListener{
public:
    SKPaymentQueueListener(){};
    virtual ~SKPaymentQueueListener(){};
    virtual void UpdatedTransactionsCallBack(std::list<SKPaymentTransactionWraper*> appStorePaymentTransactions) = 0;
};

class SKPaymentQueueWraper{
public:
    static SKPaymentQueueWraper *getInstance();
    static void destroyInstance();
public:
    SKPaymentQueueWraper();
    ~SKPaymentQueueWraper();
    void purchase(SKPaymentQueueListener *listener, std::string products_id,int quantity);
    void restorePurchase(SKPaymentQueueListener *listener );
    void completeTransaction(std::string transactionIdentifier);
};
