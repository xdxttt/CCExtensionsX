#include "GoogleIabWraper.h"
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos/platform/android/jni/JniHelper.h"
#include <jni.h>

GoogleIabWraper*s_GoogleIabWraper = NULL;
GoogleIabListener *s_GoogleIabListener = NULL;

pthread_mutex_t resultLock;

class OnIabSetupFinishedListener{
public:
    OnIabSetupFinishedListener(){
        result = NULL;
    }
    
    ~OnIabSetupFinishedListener(){
        if(result){
            delete result;
        }
    }
public:
    IabResultWraper *result;
};

class QueryInventoryFinishedListenerArgs{
    public:
    QueryInventoryFinishedListenerArgs(){
        result = NULL;
        inventory = NULL;
    }
    ~QueryInventoryFinishedListenerArgs(){
        if(result){
            delete result;
        }
        if(inventory){
            delete inventory;
        }
    }

    IabResultWraper *result;
    InventoryWraper *inventory;
};

class OnIabPurchaseFinishedListenerArgs{
    public:
    OnIabPurchaseFinishedListenerArgs(){
        result = NULL;
        purchase = NULL;
    }
    ~OnIabPurchaseFinishedListenerArgs(){
        if(result){
            delete result;
        }
        if(purchase){
            delete purchase;
        }
    }

    IabResultWraper *result;
    PurchaseWraper *purchase;
};
class OnConsumeFinishedListenerArgs{
    public:
    OnConsumeFinishedListenerArgs(){
        result = NULL;
        purchase = NULL;
    }

    ~OnConsumeFinishedListenerArgs(){
        if(result){
            delete result;
        }
        if(purchase){
            delete purchase;
        }
    }

public:
    IabResultWraper *result;
    PurchaseWraper *purchase;
};
OnIabSetupFinishedListener *g_OnIabSetupFinishedListener = NULL;
QueryInventoryFinishedListenerArgs *g_QueryInventoryFinishedListenerArgs = NULL;
OnIabPurchaseFinishedListenerArgs *g_OnIabPurchaseFinishedListenerArgs = NULL;
OnConsumeFinishedListenerArgs *g_OnConsumeFinishedListenerArgs = NULL;



JNIEXPORT void JNICALL Java_com_malom_ccextensions_GoogleIabWraper_OnIabSetupFinishedListener(JNIEnv* env, jobject thiz,jobject result){
    cocos2d::log("%s","Java_com_malom_ccextensions_GoogleIabWraper_OnIabSetupFinishedListener");
    jmethodID methodId;
    jstring retStr;
    jint retInt ;
    
    IabResultWraper *iabResultWraper = new IabResultWraper();
    
    methodId = env->GetMethodID(env->GetObjectClass(result), "getResponse","()I");
    retInt = env->CallIntMethod(result,methodId);
    iabResultWraper->mResponse = (int)retInt;
    
    methodId = env->GetMethodID(env->GetObjectClass(result), "getMessage","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(result,methodId);
    iabResultWraper->mMessage = cocos2d::JniHelper::jstring2string(retStr);
    
    pthread_mutex_lock(&resultLock);
    g_OnIabSetupFinishedListener = new OnIabSetupFinishedListener();
    g_OnIabSetupFinishedListener->result = iabResultWraper;
    pthread_mutex_unlock(&resultLock);
}


JNIEXPORT void JNICALL Java_com_malom_ccextensions_GoogleIabWraper_QueryInventoryFinishedListener(JNIEnv* env, jobject thiz,jobject result,jobject inventory){

    jmethodID methodId;
    jstring retStr;
    jint retInt;
    IabResultWraper *iabResultWraper = NULL;
    if (result) {
        iabResultWraper = new IabResultWraper();
        methodId = env->GetMethodID(env->GetObjectClass(result), "getResponse","()I");
        retInt = env->CallIntMethod(result,methodId);
        iabResultWraper->mResponse = (int)retInt;
        
        methodId = env->GetMethodID(env->GetObjectClass(result), "getMessage","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(result,methodId);
        iabResultWraper->mMessage = cocos2d::JniHelper::jstring2string(retStr);
    }
    InventoryWraper *inventoryWraper = NULL;
    if(inventory){
        inventoryWraper = new InventoryWraper();
        
        jfieldID mSkuMap = env->GetFieldID(env->GetObjectClass(inventory),"mSkuMap", "Ljava/util/Map;");
        jobject mSkuMapObj = env->GetObjectField(inventory,mSkuMap);
        
        methodId = env->GetMethodID(env->GetObjectClass(mSkuMapObj), "entrySet","()Ljava/util/Set;");
        jobject setObj = env->CallObjectMethod(mSkuMapObj,methodId);
        
        methodId = env->GetMethodID(env->GetObjectClass(setObj), "iterator","()Ljava/util/Iterator;");
        jobject entrysObj = env->CallObjectMethod(setObj,methodId);

        methodId = env->GetMethodID(env->GetObjectClass(entrysObj), "hasNext","()Z");
        jboolean jhasNext = env->CallBooleanMethod(entrysObj,methodId);
        while ((bool)jhasNext) {
            
            methodId = env->GetMethodID(env->GetObjectClass(entrysObj), "next","()Ljava/lang/Object;");
            jobject entryObj = env->CallObjectMethod(entrysObj,methodId);
            
            methodId = env->GetMethodID(env->GetObjectClass(entryObj), "getKey","()Ljava/lang/Object;");
            jstring keyStr = (jstring)env->CallObjectMethod(entryObj,methodId);
            
            methodId = env->GetMethodID(env->GetObjectClass(entryObj), "getValue","()Ljava/lang/Object;");
            jobject SkuDetailsObj = env->CallObjectMethod(entryObj,methodId);
            
            SkuDetailsWraper *skuDetailsWraper = new SkuDetailsWraper();
            
            inventoryWraper->mSkuMap[cocos2d::JniHelper::jstring2string(keyStr)] = skuDetailsWraper;

            methodId = env->GetMethodID(env->GetObjectClass(SkuDetailsObj), "getSku","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(SkuDetailsObj,methodId);
            skuDetailsWraper->mSku = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(SkuDetailsObj), "getType","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(SkuDetailsObj,methodId);
            skuDetailsWraper->mType = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(SkuDetailsObj), "getPrice","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(SkuDetailsObj,methodId);
            skuDetailsWraper->mPrice = cocos2d::JniHelper::jstring2string(retStr);
    
            methodId = env->GetMethodID(env->GetObjectClass(SkuDetailsObj), "getTitle","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(SkuDetailsObj,methodId);
            skuDetailsWraper->mTitle = cocos2d::JniHelper::jstring2string(retStr);
    
            methodId = env->GetMethodID(env->GetObjectClass(SkuDetailsObj), "getDescription","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(SkuDetailsObj,methodId);
            skuDetailsWraper->mDescription = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(SkuDetailsObj), "getCurrencyCode","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(SkuDetailsObj,methodId);
            skuDetailsWraper->mCurrencyCode = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(entrysObj), "hasNext","()Z");
            jhasNext = env->CallBooleanMethod(entrysObj,methodId);
        }
        
        
        jfieldID mPurchaseMapMid = env->GetFieldID(env->GetObjectClass(inventory),"mPurchaseMap", "Ljava/util/Map;");
        jobject mPurchaseMapObj = env->GetObjectField(inventory,mPurchaseMapMid);
        
        methodId = env->GetMethodID(env->GetObjectClass(mPurchaseMapObj), "entrySet","()Ljava/util/Set;");
        setObj = env->CallObjectMethod(mPurchaseMapObj,methodId);
        
        methodId = env->GetMethodID(env->GetObjectClass(setObj), "iterator","()Ljava/util/Iterator;");
        entrysObj = env->CallObjectMethod(setObj,methodId);
        
        methodId = env->GetMethodID(env->GetObjectClass(entrysObj), "hasNext","()Z");
        jhasNext = env->CallBooleanMethod(entrysObj,methodId);
        while ((bool)jhasNext) {
            
            methodId = env->GetMethodID(env->GetObjectClass(entrysObj), "next","()Ljava/lang/Object;");
            jobject entryObj = env->CallObjectMethod(entrysObj,methodId);
            
            methodId = env->GetMethodID(env->GetObjectClass(entryObj), "getKey","()Ljava/lang/Object;");
            jstring keyStr = (jstring)env->CallObjectMethod(entryObj,methodId);
            
            methodId = env->GetMethodID(env->GetObjectClass(entryObj), "getValue","()Ljava/lang/Object;");
            jobject purchase = env->CallObjectMethod(entryObj,methodId);
            
            PurchaseWraper *purchaseWraper = new PurchaseWraper();
            
            inventoryWraper->mPurchaseMap[cocos2d::JniHelper::jstring2string(keyStr)] = purchaseWraper;
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getItemType","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(purchase,methodId);
            purchaseWraper->mItemType = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getOrderId","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(purchase,methodId);
            purchaseWraper->mOrderId = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getPackageName","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(purchase,methodId);
            purchaseWraper->mPackageName = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getSku","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(purchase,methodId);
            purchaseWraper->mSku = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getPurchaseTime","()J");
            jlong retlong = env->CallLongMethod(purchase,methodId);
            purchaseWraper->mPurchaseTime = (long)retlong;
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getPurchaseState","()I");
            retInt = env->CallIntMethod(purchase,methodId);
            purchaseWraper->mPurchaseState = (int)retInt;
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getDeveloperPayload","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(purchase,methodId);
            purchaseWraper->mDeveloperPayload = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getToken","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(purchase,methodId);
            purchaseWraper->mToken = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getOriginalJson","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(purchase,methodId);
            purchaseWraper->mOriginalJson = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(purchase), "getSignature","()Ljava/lang/String;");
            retStr = (jstring)env->CallObjectMethod(purchase,methodId);
            purchaseWraper->mSignature = cocos2d::JniHelper::jstring2string(retStr);
            
            methodId = env->GetMethodID(env->GetObjectClass(entrysObj), "hasNext","()Z");
            jhasNext = env->CallBooleanMethod(entrysObj,methodId);
        }
    }
    //TODO Safe Lock
    pthread_mutex_lock(&resultLock);
    g_QueryInventoryFinishedListenerArgs = new QueryInventoryFinishedListenerArgs();
    g_QueryInventoryFinishedListenerArgs->result = iabResultWraper;
    g_QueryInventoryFinishedListenerArgs->inventory = inventoryWraper;
    pthread_mutex_unlock(&resultLock);

}
JNIEXPORT void JNICALL Java_com_malom_ccextensions_GoogleIabWraper_OnIabPurchaseFinishedListener(JNIEnv* env, jobject thiz,jobject result,jobject purchase){
    
    jmethodID methodId;
    jstring retStr;
    jint retInt;
    IabResultWraper *iabResultWraper = NULL;
    if (result) {
         cocos2d::log("%s","OnIabPurchaseFinishedListener:result!=null");

        iabResultWraper = new IabResultWraper();
        methodId = env->GetMethodID(env->GetObjectClass(result), "getResponse","()I");
        retInt = env->CallIntMethod(result,methodId);
        iabResultWraper->mResponse = (int)retInt;
        
        methodId = env->GetMethodID(env->GetObjectClass(result), "getMessage","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(result,methodId);
        iabResultWraper->mMessage = cocos2d::JniHelper::jstring2string(retStr);
    }
   
    PurchaseWraper *purchaseWraper = NULL;
    if (purchase) {
        cocos2d::log("%s","OnIabPurchaseFinishedListener :purchase!=null");
        purchaseWraper = new PurchaseWraper();
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getItemType","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(purchase,methodId);
        purchaseWraper->mItemType = cocos2d::JniHelper::jstring2string(retStr);
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getOrderId","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(purchase,methodId);
        purchaseWraper->mOrderId = cocos2d::JniHelper::jstring2string(retStr);
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getPackageName","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(purchase,methodId);
        purchaseWraper->mPackageName = cocos2d::JniHelper::jstring2string(retStr);
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getSku","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(purchase,methodId);
        purchaseWraper->mSku = cocos2d::JniHelper::jstring2string(retStr);
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getPurchaseTime","()J");
        jlong retlong = env->CallLongMethod(purchase,methodId);
        purchaseWraper->mPurchaseTime = (long)retlong;
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getPurchaseState","()I");
        retInt = env->CallIntMethod(purchase,methodId);
        purchaseWraper->mPurchaseState = (int)retInt;
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getDeveloperPayload","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(purchase,methodId);
        purchaseWraper->mDeveloperPayload = cocos2d::JniHelper::jstring2string(retStr);
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getToken","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(purchase,methodId);
        purchaseWraper->mToken = cocos2d::JniHelper::jstring2string(retStr);
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getOriginalJson","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(purchase,methodId);
        purchaseWraper->mOriginalJson = cocos2d::JniHelper::jstring2string(retStr);
        
        methodId = env->GetMethodID(env->GetObjectClass(purchase), "getSignature","()Ljava/lang/String;");
        retStr = (jstring)env->CallObjectMethod(purchase,methodId);
        purchaseWraper->mSignature = cocos2d::JniHelper::jstring2string(retStr);
    }

    pthread_mutex_lock(&resultLock);
    g_OnIabPurchaseFinishedListenerArgs = new OnIabPurchaseFinishedListenerArgs();
    g_OnIabPurchaseFinishedListenerArgs->result = iabResultWraper;
    g_OnIabPurchaseFinishedListenerArgs->purchase = purchaseWraper;
    pthread_mutex_unlock(&resultLock);

}


JNIEXPORT void JNICALL Java_com_malom_ccextensions_GoogleIabWraper_OnConsumeFinishedListener(JNIEnv* env, jobject thiz,jobject result,jobject purchase){
    cocos2d::log("%s","Java_com_malom_ccextensions_GoogleIabWraper_OnConsumeFinishedListener");
    jmethodID methodId;
    jstring retStr;
    jint retInt ;
    
    IabResultWraper *iabResultWraper = new IabResultWraper();
    
    methodId = env->GetMethodID(env->GetObjectClass(result), "getResponse","()I");
    retInt = env->CallIntMethod(result,methodId);
    iabResultWraper->mResponse = (int)retInt;
    
    methodId = env->GetMethodID(env->GetObjectClass(result), "getMessage","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(result,methodId);
    iabResultWraper->mMessage = cocos2d::JniHelper::jstring2string(retStr);

    PurchaseWraper *purchaseWraper = new PurchaseWraper();
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getItemType","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(purchase,methodId);
    purchaseWraper->mItemType = cocos2d::JniHelper::jstring2string(retStr);
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getOrderId","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(purchase,methodId);
    purchaseWraper->mOrderId = cocos2d::JniHelper::jstring2string(retStr);
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getPackageName","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(purchase,methodId);
    purchaseWraper->mPackageName = cocos2d::JniHelper::jstring2string(retStr);
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getSku","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(purchase,methodId);
    purchaseWraper->mSku = cocos2d::JniHelper::jstring2string(retStr);
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getPurchaseTime","()J");
    jlong retlong = env->CallLongMethod(purchase,methodId);
    purchaseWraper->mSku = (long)retlong;
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getPurchaseState","()I");
    retInt = env->CallIntMethod(purchase,methodId);
    purchaseWraper->mSku = (int)retInt;
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getDeveloperPayload","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(purchase,methodId);
    purchaseWraper->mDeveloperPayload = cocos2d::JniHelper::jstring2string(retStr);
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getToken","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(purchase,methodId);
    purchaseWraper->mToken = cocos2d::JniHelper::jstring2string(retStr);
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getOriginalJson","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(purchase,methodId);
    purchaseWraper->mOriginalJson = cocos2d::JniHelper::jstring2string(retStr);
    
    methodId = env->GetMethodID(env->GetObjectClass(purchase), "getSignature","()Ljava/lang/String;");
    retStr = (jstring)env->CallObjectMethod(purchase,methodId);
    purchaseWraper->mSignature = cocos2d::JniHelper::jstring2string(retStr);
    
    pthread_mutex_lock(&resultLock);
    g_OnConsumeFinishedListenerArgs = new OnConsumeFinishedListenerArgs();
    g_OnConsumeFinishedListenerArgs->result = iabResultWraper;
    g_OnConsumeFinishedListenerArgs->purchase = purchaseWraper;
    pthread_mutex_unlock(&resultLock);
}

GoogleIabWraper::GoogleIabWraper(){
    pthread_mutex_init(&resultLock, NULL);
}
GoogleIabWraper::~GoogleIabWraper(){
    pthread_mutex_destroy(&resultLock);
}
GoogleIabWraper *GoogleIabWraper::getInstance(){
    if (s_GoogleIabWraper==NULL) {
        s_GoogleIabWraper = new GoogleIabWraper();
    }
    return s_GoogleIabWraper;
}
void GoogleIabWraper::destroyInstance(){
    if (s_GoogleIabWraper) {
        delete s_GoogleIabWraper;
    }
}
void GoogleIabWraper::update(){
    
    pthread_mutex_lock(&resultLock);
    if (g_OnIabSetupFinishedListener) {
        if (s_GoogleIabListener) {
            cocos2d::log("%s","s_GoogleIabListener->OnIabSetupFinishedListener");
            s_GoogleIabListener->OnIabSetupFinishedListener(g_OnIabSetupFinishedListener->result);
        }
        delete g_OnIabSetupFinishedListener;
        g_OnIabSetupFinishedListener = NULL;
    }
    
    if (g_QueryInventoryFinishedListenerArgs) {
        if (s_GoogleIabListener) {
            cocos2d::log("%s","s_GoogleIabListener->QueryInventoryFinishedListener");
            s_GoogleIabListener->QueryInventoryFinishedListener(g_QueryInventoryFinishedListenerArgs->result,g_QueryInventoryFinishedListenerArgs->inventory);
        }
        delete g_QueryInventoryFinishedListenerArgs;
        g_QueryInventoryFinishedListenerArgs = NULL;
    }
    
    if (g_OnIabPurchaseFinishedListenerArgs) {
        if (s_GoogleIabListener) {
            cocos2d::log("%s","s_GoogleIabListener->OnIabPurchaseFinishedListener");
            s_GoogleIabListener->OnIabPurchaseFinishedListener(g_OnIabPurchaseFinishedListenerArgs->result,g_OnIabPurchaseFinishedListenerArgs->purchase);
        }
        delete g_OnIabPurchaseFinishedListenerArgs;
        g_OnIabPurchaseFinishedListenerArgs = NULL;
    }
    
    if (g_OnConsumeFinishedListenerArgs) {
        if (s_GoogleIabListener) {
            cocos2d::log("%s","s_GoogleIabListener->OnIabPurchaseFinishedListener");
            s_GoogleIabListener->OnConsumeFinishedListener(g_OnConsumeFinishedListenerArgs->result,g_OnConsumeFinishedListenerArgs->purchase);
        }
        delete g_OnConsumeFinishedListenerArgs;
        g_OnConsumeFinishedListenerArgs = NULL;
    }
    
    pthread_mutex_unlock(&resultLock);
}

void GoogleIabWraper::startSetup(GoogleIabListener* listener){
    cocos2d::log("startSetup");

    s_GoogleIabListener = listener;
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/malom/ccextensions/GoogleIabWraper"
                                                , "startSetup"
                                                , "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID,t.methodID);
    }
}
void GoogleIabWraper::queryInventory(std::list<std::string> skulist){
    cocos2d::log("queryInventory");

    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/malom/ccextensions/GoogleIabWraper"
                                                , "queryInventory"
                                                , "([Ljava/lang/String;)V"))
    {
        
        jobjectArray argsArray = (jobjectArray)t.env->NewObjectArray(skulist.size(),
                                                                     t.env->FindClass("java/lang/String"),
                                                                     t.env->NewStringUTF(""));
        
        std::list<std::string>::iterator it;
        int i=0;
        for (it = skulist.begin(); it != skulist.end(); ++it)
        {
            t.env->SetObjectArrayElement(argsArray,i,t.env->NewStringUTF((*it).c_str()));
            i++;
        }
        t.env->CallStaticVoidMethod(t.classID, t.methodID,argsArray);
    }
}
void GoogleIabWraper::launchPurchaseFlow(std::string sku,int rc, std::string payload){
     cocos2d::log("GoogleIabWraper::launchPurchaseFlow [%s]",sku.c_str());
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/malom/ccextensions/GoogleIabWraper"
                                                , "launchPurchaseFlow"
                                                , "(Ljava/lang/String;ILjava/lang/String;)V"))
    {
        jstring jsku = t.env->NewStringUTF(sku.c_str());
        jint jrc = rc;
        jstring jplayload = t.env->NewStringUTF(payload.c_str());
        t.env->CallStaticVoidMethod(t.classID,t.methodID,jsku,jrc,jplayload);
    }
}

void GoogleIabWraper::consumeAsync(PurchaseWraper *purchase){
    cocos2d::log("consumeAsync");

    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/malom/ccextensions/GoogleIabWraper"
                                                , "consumeAsync"
                                                , "(Lorg/util/Purchase;)V"))
    {
        jclass cls = t.env->FindClass("org/util/Purchase");
        jmethodID mid = t.env->GetMethodID(cls, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        jobject purchaseObj = t.env->NewObject(cls, mid,
                                           t.env->NewStringUTF(purchase->mItemType.c_str()),
                                           t.env->NewStringUTF(purchase->mOriginalJson.c_str()),
                                           t.env->NewStringUTF(purchase->mSignature.c_str()));
        t.env->CallStaticVoidMethod(t.classID,t.methodID,purchaseObj);
    }
}


#endif
