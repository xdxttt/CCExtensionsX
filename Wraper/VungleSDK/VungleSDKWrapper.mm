#include "VungleSDKWrapper.h"
#import <VungleSDK/VungleSDK.h>
@interface VungleSDKDelegateImp : NSObject <VungleSDKDelegate>
{
}
@end

VungleSDKWrapper *s_SharedVungleSDKWrapper = NULL;
VungleSDKDelegateWrapper * s_VungleSDKDelegateWrapper = NULL;
VungleSDKDelegateImp *s_VungleSDKDelegateImp = NULL;

@implementation VungleSDKDelegateImp
#pragma mark ChartboostDelegateImp methods

- (void)vungleSDKwillShowAd{
    if (s_VungleSDKDelegateWrapper) {
        s_VungleSDKDelegateWrapper->vungleSDKwillShowAd();
    }
}
- (void)vungleSDKwillCloseAdWithViewInfo:(NSDictionary *)viewInfo willPresentProductSheet:(BOOL)willPresentProductSheet{
    if (s_VungleSDKDelegateWrapper) {
        s_VungleSDKDelegateWrapper->vungleSDKwillCloseAdWithViewInfo(nil,willPresentProductSheet);
    }
}

- (void)vungleSDKwillCloseProductSheet:(id)productSheet{
    if (s_VungleSDKDelegateWrapper) {
        s_VungleSDKDelegateWrapper->vungleSDKwillCloseProductSheet(0);
    }
}
- (void)vungleSDKAdPlayableChanged:(BOOL)isAdPlayable{
    if (s_VungleSDKDelegateWrapper) {
        s_VungleSDKDelegateWrapper->vungleSDKAdPlayableChanged(isAdPlayable);
    }
}

@end


VungleSDKWrapper::VungleSDKWrapper(){
    
}
VungleSDKWrapper::~VungleSDKWrapper(){
    
}
VungleSDKWrapper* VungleSDKWrapper::getInstance() {
    if (!s_SharedVungleSDKWrapper) {
        s_SharedVungleSDKWrapper = new VungleSDKWrapper();
    }
    if (!s_VungleSDKDelegateImp) {
        s_VungleSDKDelegateImp = [VungleSDKDelegateImp alloc];
    }
    return s_SharedVungleSDKWrapper;
}
void VungleSDKWrapper::startWithAppId(std::string appid){
    NSString *appID = [[[NSString alloc] initWithCString:appid.c_str() encoding:NSUTF8StringEncoding] autorelease];
    VungleSDK* sdk = [VungleSDK sharedSDK];
    [sdk startWithAppId:appID];
    [sdk setDelegate:s_VungleSDKDelegateImp];
}
void VungleSDKWrapper::setDelegate(VungleSDKDelegateWrapper* delegate){
    s_VungleSDKDelegateWrapper = delegate;
}
bool VungleSDKWrapper::isAdPlayable(){
    return [[VungleSDK sharedSDK] isAdPlayable];
}
bool VungleSDKWrapper::playAd(NSErrorWraper *error){
    NSError *nserror = [[NSError alloc] autorelease];
    UIViewController * viewController = [[ [ UIApplication sharedApplication ] keyWindow] rootViewController];
    BOOL ret =  [[VungleSDK sharedSDK] playAd:viewController error:&nserror];
    if (error&&nserror) {
        error->code = nserror.code;
        error->domain = [nserror.domain cStringUsingEncoding:NSUTF8StringEncoding];
    }
    return ret;
}
