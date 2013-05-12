//
//  RemoteNotification.cpp
//  Ragnarok Battle Online
//
//  Created by xudexin on 13-4-28.
//
//

#include "RemoteNotification.h"
#import <UIKit/UIKit.h>
#include "HttpClient.h"
#include "Crypto.h"
#import "AppController.h"

using namespace cocos2d::extension;

CCRemoteNotificationContent * s_CCRNInitHandler;
CCRemoteNotificationContent * s_CCRNNotificationHandler;
CCRemoteNotification* s_CCRN;

CCRemoteNotification::CCRemoteNotification(){
    s_CCRNInitHandler = NULL;
    s_CCRNNotificationHandler = NULL;
}
CCRemoteNotification::~CCRemoteNotification(){
    
}


void CCRemoteNotification::destroyInstance()
{
    if (s_CCRN) {
        s_CCRN->release();
    }

}
void CCRemoteNotification::setupServiceAddress(const char* address){
    this->address = address;
}
void CCRemoteNotification::setupServiceToken(const char *token){
    this->token = token;
}

CCRemoteNotification* CCRemoteNotification::getInstance()
{
    if (s_CCRN == NULL) {
        s_CCRN = new CCRemoteNotification();
    }
    return s_CCRN;
}
void CCRemoteNotification::reportDiviceToken(const char *divicetoken,CCObject* pTarget, SEL_CallFuncND pSelector){
    
    CCHttpRequest *request = new CCHttpRequest;
    std::string url ="";
    url.append(address);
    url.append("/service/addDeviceToken/");
    url.append(divicetoken);
    request->setUrl(url.c_str());
    
    std::string sign = CCCrypto::getInstance()->md5(url.append(token).c_str(),url.append(token).length());
    std::string postData = "";
    postData.append("sign=").append(sign);
    request->setRequestData(postData.c_str(), postData.length());
    
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(pTarget,pSelector);
    CCHttpClient::getInstance()->send(request);
}


int CCRemoteNotification::init(cocos2d::CCObject *pTarget, SEL_CallFuncND pSelector){
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes: UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert];
    
    if (pTarget) {
        s_CCRNInitHandler = new CCRemoteNotificationContent;
        s_CCRNInitHandler->pTarget = pTarget;
        s_CCRNInitHandler->pSelector = pSelector;
    }
    return 1;
}
int CCRemoteNotification::setNotificationHandler(cocos2d::CCObject *pTarget, SEL_CallFuncND pSelector){
    
    if (pTarget) {
        s_CCRNNotificationHandler = new CCRemoteNotificationContent;
        s_CCRNNotificationHandler->pTarget = pTarget;
        s_CCRNNotificationHandler->pSelector = pSelector;
    }
    return 1;
}

@implementation AppController(category)

extern CCRemoteNotificationContent * s_CCRNInitHandler;
extern CCRemoteNotificationContent * s_CCRNNotificationHandler;

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)pToken {
    
    if (s_CCRNInitHandler) {
        NSString* aStrToken = [NSString stringWithFormat:@"%@",pToken ];
        
        aStrToken = [aStrToken stringByReplacingOccurrencesOfString:@" " withString:@""];
        aStrToken = [aStrToken stringByReplacingOccurrencesOfString:@"<" withString:@""];
        aStrToken = [aStrToken stringByReplacingOccurrencesOfString:@">" withString:@""];
        
        CCObject *pTarget = s_CCRNInitHandler->pTarget;
        SEL_CallFuncND pSelector =s_CCRNInitHandler->pSelector;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(NULL,(void*)[aStrToken UTF8String]);
        }
        NSLog(@"regisger success:%@", aStrToken);
    }
}
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo{
    // 处理推送消息
    NSString* aStrNotification = [NSString stringWithFormat:@"%@", [[userInfo objectForKey:@"aps"] objectForKey:@"alert"]];
    
    if (s_CCRNInitHandler) {
        
        CCObject *pTarget = s_CCRNNotificationHandler->pTarget;
        SEL_CallFuncND pSelector =s_CCRNNotificationHandler->pSelector;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(NULL,(void*)[aStrNotification UTF8String]);
        }
        
    }else{
        
        UIAlertView *alert=[[UIAlertView alloc]initWithTitle:@"通知" message:aStrNotification delegate:self cancelButtonTitle:@"确认" otherButtonTitles:nil, nil];
        [alert show];
        [alert release];
    }
    NSLog(@"%@",aStrNotification);
    
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
    NSLog(@"Regist fail%@",error);
}
@end
