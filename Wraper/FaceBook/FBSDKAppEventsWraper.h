#pragma once
class FBSDKAppEventsWraper{
public:
    FBSDKAppEventsWraper();
    ~FBSDKAppEventsWraper();
    static FBSDKAppEventsWraper *getInstance();
    static void destroyInstance();
    void activateApp();
};