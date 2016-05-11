#pragma once
#include <set>
#include <string>

class FBSDKProfileWraper{
public:
    FBSDKProfileWraper(){};
    ~FBSDKProfileWraper(){};
    static FBSDKProfileWraper* currentProfile();
    std::string userID;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string name;
    static void enableUpdatesOnAccessTokenChange(bool enable);
};

class FBSDKAccessTokenWraper{
public:
    FBSDKAccessTokenWraper(){};
    ~FBSDKAccessTokenWraper(){};
    std::string appID;
    std::set<std::string> declinedPermissions;
    std::set<std::string> permissions;
    char refreshDate[1024];
    char expirationDate[1024];
    std::string tokenString;
    std::string userID;
    static FBSDKAccessTokenWraper* currentAccessToken();
};
class FBSDKLoginManagerLoginResultWraper{
public:
    FBSDKLoginManagerLoginResultWraper(){
        token = NULL;
    };
    ~FBSDKLoginManagerLoginResultWraper(){
        if (token) {
            delete token;
        }
    };
    FBSDKAccessTokenWraper *token;
    bool isCancelled;
    std::set<std::string> grantedPermissions;
    std::set<std::string> declinedPermissions;
};

class FBSDKLoginManagerListener{
public:
    FBSDKLoginManagerListener(){};
    virtual ~FBSDKLoginManagerListener(){};
    virtual void onLogIn(FBSDKLoginManagerLoginResultWraper* result,const char* error) = 0;
};

class FBSDKLoginManagerWraper{
public:
    FBSDKLoginManagerWraper();
    ~FBSDKLoginManagerWraper();
    static FBSDKLoginManagerWraper *getInstance();
    static void destroyInstance();
    void update();
    void logInWithReadPermissions(std::set<std::string> permissions,FBSDKLoginManagerListener *listener);
    void logInWithPublishPermissions(std::set<std::string> permissions,FBSDKLoginManagerListener *listener);
    void logOut();
    
};

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
extern "C"
{
    JNIEXPORT void JNICALL Java_com_malom_ccextensions_FBSDKLoginManagerWraper_onLoginSuccess(JNIEnv* env, jobject thiz,jobject obj);
    JNIEXPORT void JNICALL Java_com_malom_ccextensions_FBSDKLoginManagerWraper_onLoginCancel(JNIEnv* env, jobject thiz);
    JNIEXPORT void JNICALL Java_com_malom_ccextensions_FBSDKLoginManagerWraper_onLoginError(JNIEnv* env, jobject thiz,jstring string);
};
#endif
