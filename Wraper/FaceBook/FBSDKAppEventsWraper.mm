#include "FBSDKAppEventsWraper.h"
#import <FBSDKCoreKit/FBSDKCoreKit.h>

FBSDKAppEventsWraper*s_FBSDKAppEventsWraper = NULL;

FBSDKAppEventsWraper::FBSDKAppEventsWraper(){
}
FBSDKAppEventsWraper::~FBSDKAppEventsWraper(){
}
FBSDKAppEventsWraper* FBSDKAppEventsWraper::getInstance(){
    if (s_FBSDKAppEventsWraper==NULL) {
        s_FBSDKAppEventsWraper = new FBSDKAppEventsWraper();
    }
    return  s_FBSDKAppEventsWraper;
}
void FBSDKAppEventsWraper::destroyInstance(){
    if (s_FBSDKAppEventsWraper) {
        delete s_FBSDKAppEventsWraper;
    }
}
void FBSDKAppEventsWraper::activateApp(){
    [FBSDKAppEvents activateApp];
}