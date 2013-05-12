//
//  DeviceInfo.cpp
//
//  Created by xudexin on 13-4-28.
//
//

#include "DeviceInfo.h"

CCDeviceInfo* sCCDeviceInfo = NULL;

CCDeviceInfo *CCDeviceInfo::getInstance(){
    if (sCCDeviceInfo==NULL) {
        sCCDeviceInfo = new CCDeviceInfo;
    }
    return sCCDeviceInfo;
}
void CCDeviceInfo::destroyInstance(){
    if (sCCDeviceInfo) {
        delete sCCDeviceInfo;
    }
}
CCDeviceInfo::CCDeviceInfo(){
    
}
CCDeviceInfo::~CCDeviceInfo(){
    
}

std::string CCDeviceInfo::getUDID(){
    CFUUIDRef   uuid;
    CFStringRef uuidStr;
    
    uuid = CFUUIDCreate(NULL);
    assert(uuid != NULL);
    
    uuidStr = CFUUIDCreateString(NULL, uuid);
    assert(uuidStr != NULL);
    NSString *aNSString = (NSString *)uuidStr;
    NSLog(@"UDID::%@",aNSString);
    std::string ret = [aNSString UTF8String];
    return ret;
}