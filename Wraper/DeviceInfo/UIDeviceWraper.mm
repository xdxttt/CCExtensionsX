#include "UIDeviceWraper.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#include <AdSupport/AdSupport.h>
UIDeviceWraper::UIDeviceWraper(void) {
}

UIDeviceWraper::~UIDeviceWraper(void) {
}
std::string UIDeviceWraper::getDeviceType(){
    return std::string("I");
}
std::string  UIDeviceWraper::getUUID(){
    UIDevice *device_=[[UIDevice alloc] init];
    return [device_.identifierForVendor.UUIDString cStringUsingEncoding: NSUTF8StringEncoding];
}
   
std::string UIDeviceWraper::getUDID() {
    NSString* udid = NULL;
        if([[[UIDevice currentDevice] systemVersion] floatValue] >=6.0f){
            udid = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
        }else{
            CFUUIDRef uuidRef = CFUUIDCreate(kCFAllocatorDefault);
            udid =(NSString *)CFUUIDCreateString (kCFAllocatorDefault,uuidRef);
        }
        return [udid cStringUsingEncoding: NSUTF8StringEncoding];
}

std::string UIDeviceWraper::getName(){
        UIDevice *device_=[[UIDevice alloc] init];
        return [device_.name cStringUsingEncoding: NSUTF8StringEncoding];
}
std::string  UIDeviceWraper::getModel(){
    UIDevice *device_=[[UIDevice alloc] init];
    return [device_.model cStringUsingEncoding: NSUTF8StringEncoding];
}

std::string  UIDeviceWraper::getLocalizedModel(){
    UIDevice *device_=[[UIDevice alloc] init];
    return [device_.localizedModel cStringUsingEncoding: NSUTF8StringEncoding];
}

std::string  UIDeviceWraper::getSystemName(){
    UIDevice *device_=[[UIDevice alloc] init];
    return [device_.systemName cStringUsingEncoding: NSUTF8StringEncoding];
}

std::string  UIDeviceWraper::getSystemVersion(){
    UIDevice *device_=[[UIDevice alloc] init];
    return [device_.systemVersion cStringUsingEncoding: NSUTF8StringEncoding];
}

#endif




