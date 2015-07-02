#include "VungleSDKWrapper.h"
#import <VungleSDK/VungleSDK.h>

VungleSDKWrapper *s_SharedVungleSDKWrapper = NULL;

VungleSDKWrapper::VungleSDKWrapper(){
    
}
VungleSDKWrapper::~VungleSDKWrapper(){
    
}
VungleSDKWrapper* VungleSDKWrapper::getInstance() {
    if (!s_SharedVungleSDKWrapper) {
        s_SharedVungleSDKWrapper = new VungleSDKWrapper();
    }
    return s_SharedVungleSDKWrapper;
}
void VungleSDKWrapper::startWithAppId(std::string appid){
    NSString *appID = [[[NSString alloc] initWithCString:appid.c_str() encoding:NSUTF8StringEncoding] autorelease];
    VungleSDK* sdk = [VungleSDK sharedSDK];
    [sdk startWithAppId:appID];
}

bool VungleSDKWrapper::isAdPlayable(){
    return [[VungleSDK sharedSDK] isAdPlayable];
}
bool VungleSDKWrapper::playAd(NSErrorWraper *error){
    NSError *nserror = [[NSError alloc] autorelease];
    BOOL ret =  [[VungleSDK sharedSDK] playAd:[UIApplication sharedApplication].keyWindow.rootViewController error:&nserror];
    if (error&&nserror) {
        error->code = nserror.code;
        error->domain = [nserror.domain cStringUsingEncoding:NSUTF8StringEncoding];
    }
    return ret;
}
