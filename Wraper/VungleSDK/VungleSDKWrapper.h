#pragma once
#include "NSErrorWraper.h"
class VungleSDKDelegateWrapper{
public:
    VungleSDKDelegateWrapper(void){}
    ~VungleSDKDelegateWrapper(void){}
    
    void virtual vungleSDKwillShowAd() = 0;
    void virtual vungleSDKwillCloseAdWithViewInfo(std::map<std::string,std::string> *viewInfo,bool willPresentProductSheet) = 0;
    void virtual vungleSDKwillCloseProductSheet(int productSheet ) = 0;
    void virtual vungleSDKAdPlayableChanged(bool isAdPlayable) = 0;
    
};

class VungleSDKWrapper{
public:
    VungleSDKWrapper(void);
    ~VungleSDKWrapper(void);
    static VungleSDKWrapper*getInstance();
    
    void setDelegate(VungleSDKDelegateWrapper* delegate);
    
    void startWithAppId(std::string appID);
    
    bool isAdPlayable();
    
    bool playAd(NSErrorWraper *error);
};
