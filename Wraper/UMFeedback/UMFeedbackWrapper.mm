//
//  UMFeedbackWrapper.cpp
//  PuzzleWarrior
//
//  Created by xudexin on 15/5/19.
//
//

#include "UMFeedbackWrapper.h"
#import <UMFeedback.h>

UMFeedbackWrapper*s_UMFeedbackWrapper = NULL;

UMFeedbackWrapper::UMFeedbackWrapper(){
}
UMFeedbackWrapper::~UMFeedbackWrapper(){
}
UMFeedbackWrapper* UMFeedbackWrapper::getInstance(){
    if (s_UMFeedbackWrapper==NULL) {
        s_UMFeedbackWrapper = new UMFeedbackWrapper();
    }
    return  s_UMFeedbackWrapper;
}
void UMFeedbackWrapper::destroyInstance(){
    if (s_UMFeedbackWrapper) {
        delete s_UMFeedbackWrapper;
    }
}
void UMFeedbackWrapper::showFeedback(std::string appKey){
    NSString*nsstr = [[NSString alloc] initWithCString:appKey.c_str() encoding:NSUTF8StringEncoding];
    [UMFeedback showFeedback: [UIApplication sharedApplication].keyWindow.rootViewController withAppkey:nsstr];
}