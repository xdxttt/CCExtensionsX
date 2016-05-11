#pragma once
#include <map>
#include <string>
#include "cJSON.h"

#include "cocos2d.h"

class SkuDetailsWraper{
public:
    SkuDetailsWraper(){};
    ~SkuDetailsWraper(){};
    std::string mItemType;
    std::string mSku;
    std::string mType;
    std::string mPrice;
    std::string mTitle;
    std::string mDescription;
    std::string mCurrencyCode;
    std::string mJson;
};

class PurchaseWraper{
public:
    PurchaseWraper(std::string itemType,std::string originalJson,std::string signature){
        mItemType = itemType;
        mSignature = signature;
        mOriginalJson = originalJson;
        cJSON *o = cJSON_Parse(mOriginalJson.c_str());

        mOrderId = cJSON_GetObjectItem(o,"orderId")->valuestring;
        cocos2d::log("%s","orderId");

        mPackageName = cJSON_GetObjectItem(o,"packageName")->valuestring;
        cocos2d::log("%s","packageName");

        mSku = cJSON_GetObjectItem(o,"productId")->valuestring;
        cocos2d::log("%s","productId");

        mPurchaseTime = cJSON_GetObjectItem(o,"purchaseTime")->valueint;
        cocos2d::log("%s","purchaseTime");

        mPurchaseState = cJSON_GetObjectItem(o,"purchaseState")->valueint;
        cocos2d::log("%s","purchaseState");

        if (cJSON_GetObjectItem(o,"developerPayload")) {
            mDeveloperPayload = cJSON_GetObjectItem(o,"developerPayload")->valuestring;
        }else{
            mDeveloperPayload = "";
        }
        
        if (cJSON_GetObjectItem(o,"token")) {
            mToken = cJSON_GetObjectItem(o,"token")->valuestring;
            cocos2d::log("%s","token");

        }else{
            mToken = cJSON_GetObjectItem(o,"purchaseToken")->valuestring;
            cocos2d::log("%s","purchaseToken");
        }
//        
//        {"orderId":"GPA.1317-0119-8655-37685","packageName":"org.tjgame.PuzzleWarrior","productId":"puzzle_warrior_gem_0.99","purchaseTime":1447141604581,"purchaseState":0,"purchaseToken":"opcpdcdkjpkadngcjjdndhkk.AO-J1OxRYq6xjZ0TdkY1KGwACZPKHAwzTvZcDwerX3ZIWaTS237fd3HIJMFDoZAW-enUsmxZ_1x3P2oZEqnoVUyCpM16shoRVloTGGB8b8lAtIQ9Hh2AtuOqHTUoZv4Vx-yAOQgk8794Ov37fR5F-zuQ-5Lc_Qf1eA"}
//        
        cocos2d::log("%s","cJSON_Delete");

        cJSON_Delete(o);
    };
    PurchaseWraper(){};
    ~PurchaseWraper(){};
    
    std::string mItemType;  // ITEM_TYPE_INAPP or ITEM_TYPE_SUBS
    std::string mOrderId;
    std::string mPackageName;
    std::string mSku;
    long mPurchaseTime;
    int mPurchaseState; // 0 ( purchased), 1 (canceled), or 2 (refunded)
    std::string mDeveloperPayload;
    std::string mToken;
    std::string mOriginalJson;
    std::string mSignature;
    
};

class InventoryWraper{
public:
    InventoryWraper(){};
    ~InventoryWraper(){};
    std::map<std::string,SkuDetailsWraper*> mSkuMap;
    std::map<std::string,PurchaseWraper*> mPurchaseMap;
};

enum BILLING_RESPONSE_RESULT{
    OK = 0,
    USER_CANCELED = 1,
    BILLING_UNAVAILABLE = 3,
    ITEM_UNAVAILABLE = 4,
    DEVELOPER_ERROR = 5,
    ERROR = 6,
    ITEM_ALREADY_OWNED = 7,
    ITEM_NOT_OWNED = 8
} ;


class IabResultWraper{
public:
    IabResultWraper(){};
    ~IabResultWraper(){};
    int mResponse;
    std::string mMessage;
};

class GoogleIabListener{
public:
    GoogleIabListener(){};
    virtual ~GoogleIabListener(){};
    virtual void OnIabSetupFinishedListener(IabResultWraper *result) = 0;
    virtual void QueryInventoryFinishedListener(IabResultWraper *result, InventoryWraper *inventory) = 0;
    virtual void OnIabPurchaseFinishedListener(IabResultWraper *result, PurchaseWraper *purchase) = 0;
    virtual void OnConsumeFinishedListener(IabResultWraper *result, PurchaseWraper *purchase) = 0;
};

class GoogleIabWraper{
public:
    GoogleIabWraper();
    ~GoogleIabWraper();
    static GoogleIabWraper *getInstance();
    static void destroyInstance();
    void update();
    void startSetup(GoogleIabListener* listener);
    void queryInventory(std::list<std::string> skulist);
    void launchPurchaseFlow(std::string sku,int rc, std::string payload);
    void consumeAsync(PurchaseWraper *purchase);
    
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
extern "C"
{
    JNIEXPORT void JNICALL Java_com_malom_ccextensions_GoogleIabWraper_OnIabSetupFinishedListener(JNIEnv* env, jobject thiz,jobject result);
    JNIEXPORT void JNICALL Java_com_malom_ccextensions_GoogleIabWraper_QueryInventoryFinishedListener(JNIEnv* env, jobject thiz,jobject result,jobject inventory);
    JNIEXPORT void JNICALL Java_com_malom_ccextensions_GoogleIabWraper_OnIabPurchaseFinishedListener(JNIEnv* env, jobject thiz,jobject result,jobject purchase);
    JNIEXPORT void JNICALL Java_com_malom_ccextensions_GoogleIabWraper_OnConsumeFinishedListener(JNIEnv* env, jobject thiz,jobject result,jobject purchase);
};
#endif
