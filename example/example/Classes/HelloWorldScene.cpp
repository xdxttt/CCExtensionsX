#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "HttpClient.h"


#include "cJSON.h"
#include "APPStoreIAP.h"
#include "DeviceInfo.h"
#include "RemoteNotification.h"
#include "Config.h"

using namespace cocos2d;
using namespace CocosDenshion;

using namespace cocos2d::extension;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
    CCConfig::getInstance()->setupServiceAddress("http://115.28.42.117/xGameTools/index.php");
    CCConfig::getInstance()->setupServiceToken("122112");
    
    CCAppStoreIAP::getInstance()->setupServiceAddress("http://115.28.42.117/xGameTools/index.php");
    CCAppStoreIAP::getInstance()->setupServiceToken("122112");
    
    CCRemoteNotification::getInstance()->setupServiceAddress("http://115.28.42.117/xGameTools/index.php");
    CCAppStoreIAP::getInstance()->setupServiceToken("122112");
    
    
    CCConfig::getInstance()->getModelConf("purchase",this, callfuncND_selector(HelloWorld::getProductsConfCallBack));
    CCConfig::getInstance()->getModelConf("purchaseRewards",this, callfuncND_selector(HelloWorld::getConfCallBack));
    CCConfig::getInstance()->getModelConf("loginRewards",this, callfuncND_selector(HelloWorld::getConfCallBack));
    CCConfig::getInstance()->getModelConf("dailyChallenge",this, callfuncND_selector(HelloWorld::getConfCallBack));
    CCConfig::getInstance()->getModelConf("dailyRewards",this, callfuncND_selector(HelloWorld::getConfCallBack));
    
    CCRemoteNotification::getInstance()->init(this, callfuncND_selector(HelloWorld::initRemoteNotificationCallBack));
    CCRemoteNotification::getInstance()->setNotificationHandler(this, callfuncND_selector(HelloWorld::remoteNotification));
    
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::initRemoteNotificationCallBack(cocos2d::CCNode *node, void *data){
    CCLOG("initRemoteNotificationCallBack dicive token %s:",(char*)data);
    CCRemoteNotification::getInstance()->reportDiviceToken((char*)data,this, callfuncND_selector(HelloWorld::getProductsConfCallBack));
}

void HelloWorld::remoteNotification(cocos2d::CCNode *node, void *data){
    CCLOG("remoteNotification %s:",(char*)data);
    
}
void HelloWorld::getConfCallBack(cocos2d::CCNode *node, void *data){
    CCHttpResponse *reponseObj = (CCHttpResponse *)data;
    std::string respData(reponseObj->getResponseData()->begin(),reponseObj->getResponseData()->end());
    CCLog("ProductsConf: \r\n%s",respData.c_str());

    cJSON *reponse = cJSON_Parse((char*)respData.c_str());
    if (reponse) {
        
    }
}

void HelloWorld::getProductsConfCallBack(cocos2d::CCNode *node, void *data){
    CCHttpResponse *reponseObj = (CCHttpResponse *)data;
        std::string respData(reponseObj->getResponseData()->begin(),reponseObj->getResponseData()->end());
    CCLog("ProductsConf: \r\n%s",respData.c_str());

    cJSON *reponse = cJSON_Parse((char*)respData.c_str());
    if (reponse&& cJSON_GetObjectItem(reponse, "ret")->valueint==1000) {
        
        cJSON *productArray = cJSON_GetObjectItem(reponse, "data");
        
        std::list<std::string> products_ids;
        
        for (int i = 0; i<cJSON_GetArraySize(productArray); i++) {
            cJSON *item = cJSON_GetArrayItem(productArray, i);
            products_ids.push_back(cJSON_GetObjectItem(item, "product_id")->valuestring);
        }
        CCAppStoreIAP::getInstance()->requestSKProducts(products_ids, this, callfuncND_selector(HelloWorld::requestSKProductsCallBack));
    }
}


void HelloWorld::requestSKProductsCallBack(cocos2d::CCNode *node, void *data){
    std::list<CCAppStoreProducts*>* list =(std::list<CCAppStoreProducts*>*)data;
    
    for (std::list<CCAppStoreProducts*>::iterator iter = list->begin(); iter!=list->end(); iter++) {
        CCAppStoreProducts* product = *iter;
        CCLOG("CCProducts:");
        CCLOG("localizedDescription: %s",product->localizedDescription.c_str());
        CCLOG("localizedTitle:%s",product->localizedTitle.c_str());
        CCLOG("priceLocale:%s",product->priceLocale.c_str());
        CCLOG("price:%f",product->price);
        CCLOG("productIdentifier:%s",product->productIdentifier.c_str());
        
        CCAppStoreIAP::getInstance()->pay(product->productIdentifier, 2, this,callfuncND_selector(HelloWorld::payCallBack));
    }
    
}
void HelloWorld::payCallBack(cocos2d::CCNode *node, void *data){
    std::list<CCAppStorePaymentTransaction*>* list =(std::list<CCAppStorePaymentTransaction*>*)data;
    
    for (std::list<CCAppStorePaymentTransaction*>::iterator iter = list->begin(); iter!=list->end(); iter++) {
        CCAppStorePaymentTransaction* payment = *iter;
        CCLOG("CCPaymentTransaction:");
        CCLOG("transactionState: %d",payment->transactionState);
        CCLOG("transactionIdentifier:%s",payment->transactionIdentifier.c_str());
        //CCLOG("transactionDate:%s",payment->transactionDate);
        if(payment->transactionReceipt){
            CCLOG("transactionReceipt:%s",payment->transactionReceipt);
        }
        CCLOG("error:%s",payment->error.c_str());
        
        CCLOG("quantity: %d",payment->payment.quantity);
        CCLOG("productIdentifier:%s",payment->payment.productIdentifier.c_str());
        //      CCLOG("quantity:%d",payment->payment.quantity);
        
        if (payment->transactionState==CCAppStorePaymentTransactionStatePurchased&&payment->transactionIdentifier.size()>0) {
            CCAppStoreIAP::getInstance()->verify("1",payment->transactionIdentifier,payment->transactionReceipt, this, callfuncND_selector(HelloWorld::verifyCallBack));
        }else{
            CCAppStoreIAP::getInstance()->completeTransaction(payment->transactionIdentifier);
        }
    }
}
void HelloWorld::verifyCallBack(cocos2d::CCNode *node, void *resp){
    
    extension::CCHttpResponse *response  = (extension::CCHttpResponse *)resp;
	std::string str(response->getResponseData()->begin(), response->getResponseData()->end() );
    CCLog("[%d] : http://%s   \r\n",response->getResponseCode(),response->getHttpRequest()->getUrl());
    CCLog("toJSON: --- begin ---\r\n %s",str.c_str());
    CCLog("toJSON: --- end ---\r\n");
    cJSON *verifyJSON  =  cJSON_Parse(str.c_str());
    if (verifyJSON) {
        cJSON *data = cJSON_GetObjectItem(verifyJSON,"data");
        cJSON *receipt = cJSON_GetObjectItem(data,"receipt");
        cJSON *transaction_id = cJSON_GetObjectItem(receipt,"transaction_id");
        CCAppStoreIAP::getInstance()->completeTransaction(transaction_id->valuestring);
    }
    
}

