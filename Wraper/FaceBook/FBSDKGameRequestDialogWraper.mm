#include "FBSDKGameRequestDialogWraper.h"
#include "FBSDKGameRequestDialogDelegateImp.h"

FBSDKGameRequestDialogWraper *s_FBSDKGameRequestDialogWraper = NULL;
FBSDKGameRequestDialogDelegateImp *s_FBSDKGameRequestDialogDelegateImp;

FBSDKGameRequestDialogWraper::FBSDKGameRequestDialogWraper(){
}
FBSDKGameRequestDialogWraper::~FBSDKGameRequestDialogWraper(){
}
FBSDKGameRequestDialogWraper* FBSDKGameRequestDialogWraper::getInstance(){
    if (s_FBSDKGameRequestDialogWraper==NULL) {
        s_FBSDKGameRequestDialogWraper = new FBSDKGameRequestDialogWraper();
        s_FBSDKGameRequestDialogDelegateImp = [[FBSDKGameRequestDialogDelegateImp alloc] init];
    }
    return s_FBSDKGameRequestDialogWraper;
}
void FBSDKGameRequestDialogWraper::destroyInstance(){
    if (s_FBSDKGameRequestDialogWraper) {
        delete s_FBSDKGameRequestDialogWraper;
        [s_FBSDKGameRequestDialogDelegateImp release];
    }
}

void FBSDKGameRequestDialogWraper::showWithContent(){
    
    FBSDKGameRequestContent *gameRequestContent = [[FBSDKGameRequestContent alloc] init];
    gameRequestContent.message = @"Take this bomb to blast your way to victory!";
    gameRequestContent.to = @[@"RECIPIENT_USER_ID"];
    gameRequestContent.objectID = @"YOUR_OBJECT_ID";
    [FBSDKGameRequestDialog showWithContent:gameRequestContent delegate:s_FBSDKGameRequestDialogDelegateImp];
}