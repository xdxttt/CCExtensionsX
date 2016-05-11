#include "FBSDKLoginManagerWraper.h"
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos/platform/android/jni/JniHelper.h"
#include <jni.h>
FBSDKLoginManagerWraper*s_FBSDKLoginManagerWraper = NULL;
FBSDKLoginManagerListener *s_FBSDKLoginManagerListener = NULL;

class OnFBSDKLoginManagerListener{
public:
    OnFBSDKLoginManagerListener(){
        result = NULL;
        error = NULL;
    }
    
    ~OnFBSDKLoginManagerListener(){
        if(result){
            delete result;
        }
        if (error) {
            delete error;
        }
    }
public:
    FBSDKLoginManagerLoginResultWraper *result;
    const char* error;
};
pthread_mutex_t fbLock;
OnFBSDKLoginManagerListener *g_OnFBSDKLoginManagerListener = NULL;


FBSDKProfileWraper* FBSDKProfileWraper::currentProfile(){
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/facebook/Profile"
                                                , "getCurrentProfile"
                                                , "()Lcom/facebook/Profile;"))
    {
        jobject obj_profile = t.env->CallStaticObjectMethod(t.classID, t.methodID);
        if (obj_profile) {
            FBSDKProfileWraper *profile = new FBSDKProfileWraper();

            jmethodID mid;
            jstring retStr;
            
            mid = t.env->GetMethodID(t.env->GetObjectClass(obj_profile), "getId","()Ljava/lang/String;");
            retStr = (jstring)t.env->CallObjectMethod(obj_profile,mid);
            profile->userID = cocos2d::JniHelper::jstring2string(retStr);
            
            mid = t.env->GetMethodID(t.env->GetObjectClass(obj_profile), "getFirstName","()Ljava/lang/String;");
            retStr = (jstring)t.env->CallObjectMethod(obj_profile,mid);
            profile->firstName = cocos2d::JniHelper::jstring2string(retStr);
            
            mid = t.env->GetMethodID(t.env->GetObjectClass(obj_profile), "getMiddleName","()Ljava/lang/String;");
            retStr = (jstring)t.env->CallObjectMethod(obj_profile,mid);
            profile->middleName = cocos2d::JniHelper::jstring2string(retStr);
            
            mid = t.env->GetMethodID(t.env->GetObjectClass(obj_profile), "getLastName","()Ljava/lang/String;");
            retStr = (jstring)t.env->CallObjectMethod(obj_profile,mid);
            profile->lastName = cocos2d::JniHelper::jstring2string(retStr);
            
            mid = t.env->GetMethodID(t.env->GetObjectClass(obj_profile), "getName","()Ljava/lang/String;");
            retStr = (jstring)t.env->CallObjectMethod(obj_profile,mid);
            profile->name = cocos2d::JniHelper::jstring2string(retStr);
            
            return profile;
        }else{
            return  NULL;
        }
    }

    
}
void FBSDKProfileWraper::enableUpdatesOnAccessTokenChange(bool enable){
    //[FBSDKProfile enableUpdatesOnAccessTokenChange:(BOOL)enable];
}
FBSDKAccessTokenWraper* FBSDKAccessTokenWraper::currentAccessToken(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/facebook/AccessToken"
                                                , "getCurrentAccessToken"
                                                , "()Lcom/facebook/AccessToken;"))
    {
        jobject obj_accessToken = t.env->CallStaticObjectMethod(t.classID, t.methodID);
        if (obj_accessToken) {
            FBSDKAccessTokenWraper *accessToken = new FBSDKAccessTokenWraper();
            
            jmethodID mid;
            jstring retStr;
            
            mid = t.env->GetMethodID(t.env->GetObjectClass(obj_accessToken), "getUserId","()Ljava/lang/String;");
            retStr = (jstring)t.env->CallObjectMethod(obj_accessToken,mid);
            accessToken->userID = cocos2d::JniHelper::jstring2string(retStr);
            
            mid = t.env->GetMethodID(t.env->GetObjectClass(obj_accessToken), "getToken","()Ljava/lang/String;");
            retStr = (jstring)t.env->CallObjectMethod(obj_accessToken,mid);
            accessToken->tokenString = cocos2d::JniHelper::jstring2string(retStr);
            
            mid = t.env->GetMethodID(t.env->GetObjectClass(obj_accessToken), "getApplicationId","()Ljava/lang/String;");
            retStr = (jstring)t.env->CallObjectMethod(obj_accessToken,mid);
            accessToken->appID = cocos2d::JniHelper::jstring2string(retStr);
            
            return accessToken;
        }else{
            return  NULL;
        }
    }else{
    
    }
}

FBSDKLoginManagerWraper::FBSDKLoginManagerWraper(){
}
FBSDKLoginManagerWraper::~FBSDKLoginManagerWraper(){
}
FBSDKLoginManagerWraper* FBSDKLoginManagerWraper::getInstance(){
    if (s_FBSDKLoginManagerWraper==NULL) {
        s_FBSDKLoginManagerWraper = new FBSDKLoginManagerWraper();
    }
    return s_FBSDKLoginManagerWraper;
}
void FBSDKLoginManagerWraper::destroyInstance(){
    if (s_FBSDKLoginManagerWraper) {
        delete s_FBSDKLoginManagerWraper;
    }
}
void FBSDKLoginManagerWraper::logOut(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/malom/ccextensions/FBSDKLoginManagerWraper"
                                                , "logOut"
                                                , "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
}
void FBSDKLoginManagerWraper::logInWithPublishPermissions(std::set<std::string> permissions,FBSDKLoginManagerListener *listener){
    s_FBSDKLoginManagerListener = listener;
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/malom/ccextensions/FBSDKLoginManagerWraper"
                                                , "logInWithPublishPermissions"
                                                , "([Ljava/lang/String;)V"))
    {
        jobjectArray argsArray = (jobjectArray)t.env->NewObjectArray(permissions.size(),
                                               t.env->FindClass("java/lang/String"),
                                               t.env->NewStringUTF(""));
        
        std::set<std::string>::iterator it;
        int i=0;
        for (it = permissions.begin(); it != permissions.end(); ++it)
        {
            t.env->SetObjectArrayElement(argsArray,i,t.env->NewStringUTF((*it).c_str()));
            i++;
        }
        t.env->CallStaticVoidMethod(t.classID, t.methodID,argsArray);
    }
}
void FBSDKLoginManagerWraper::logInWithReadPermissions(std::set<std::string> permissions,FBSDKLoginManagerListener *listener){
    s_FBSDKLoginManagerListener = listener;
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/malom/ccextensions/FBSDKLoginManagerWraper"
                                                , "logInWithReadPermissions"
                                                , "([Ljava/lang/String;)V"))
    {
        jobjectArray argsArray = (jobjectArray)t.env->NewObjectArray(permissions.size(),
                                                                     t.env->FindClass("java/lang/String"),
                                                                     t.env->NewStringUTF(""));
        
        std::set<std::string>::iterator it;
        int i=0;
        for (it = permissions.begin(); it != permissions.end(); ++it)
        {
            t.env->SetObjectArrayElement(argsArray,i,t.env->NewStringUTF((*it).c_str()));
            i++;
        }
        t.env->CallStaticVoidMethod(t.classID, t.methodID,argsArray);
    }
}
void FBSDKLoginManagerWraper::update(){
    pthread_mutex_lock(&fbLock);
    if (g_OnFBSDKLoginManagerListener) {
        if (s_FBSDKLoginManagerListener) {
            s_FBSDKLoginManagerListener->onLogIn(g_OnFBSDKLoginManagerListener->result,g_OnFBSDKLoginManagerListener->error);
        }
        delete g_OnFBSDKLoginManagerListener;
        g_OnFBSDKLoginManagerListener = NULL;
    }
    pthread_mutex_unlock(&fbLock);
}


JNIEXPORT void JNICALL Java_com_malom_ccextensions_FBSDKLoginManagerWraper_onLoginSuccess(JNIEnv* env, jobject thiz,jobject obj)
{

    jmethodID methodId = env->GetMethodID(env->GetObjectClass(obj), "getAccessToken","()Lcom/facebook/AccessToken;");
    jobject obj_accessToken = env->CallObjectMethod(obj,methodId);
    
    FBSDKLoginManagerLoginResultWraper *result = new FBSDKLoginManagerLoginResultWraper();
    result->isCancelled = false;
    result->token = new FBSDKAccessTokenWraper();
    
    methodId = env->GetMethodID(env->GetObjectClass(obj_accessToken), "getUserId","()Ljava/lang/String;");
    jstring str_userID = (jstring)env->CallObjectMethod(obj_accessToken,methodId);
    result->token->userID = cocos2d::JniHelper::jstring2string(str_userID);
    
    methodId = env->GetMethodID(env->GetObjectClass(obj_accessToken), "getToken","()Ljava/lang/String;");
    jstring str_tokenString = (jstring)env->CallObjectMethod(obj_accessToken,methodId);
    result->token->tokenString = cocos2d::JniHelper::jstring2string(str_tokenString);
    
    methodId = env->GetMethodID(env->GetObjectClass(obj_accessToken), "getApplicationId","()Ljava/lang/String;");
    jstring str_appID = (jstring)env->CallObjectMethod(obj_accessToken,methodId);
    result->token->appID = cocos2d::JniHelper::jstring2string(str_appID);

    pthread_mutex_lock(&fbLock);
    g_OnFBSDKLoginManagerListener = new OnFBSDKLoginManagerListener();
    g_OnFBSDKLoginManagerListener->result = result;
    pthread_mutex_unlock(&fbLock);

}
JNIEXPORT void JNICALL Java_com_malom_ccextensions_FBSDKLoginManagerWraper_onLoginCancel(JNIEnv* env, jobject thiz)
{
    FBSDKLoginManagerLoginResultWraper *result = new FBSDKLoginManagerLoginResultWraper();
    result->isCancelled = true;
    result->token = NULL;
    
    pthread_mutex_lock(&fbLock);
    g_OnFBSDKLoginManagerListener = new OnFBSDKLoginManagerListener();
    g_OnFBSDKLoginManagerListener->result = result;
    pthread_mutex_unlock(&fbLock);
    
}
JNIEXPORT void JNICALL Java_com_malom_ccextensions_FBSDKLoginManagerWraper_onLoginError(JNIEnv* env, jobject thiz,jstring string)
{
    pthread_mutex_lock(&fbLock);
    g_OnFBSDKLoginManagerListener = new OnFBSDKLoginManagerListener();
    g_OnFBSDKLoginManagerListener->error = env->GetStringUTFChars(string, NULL);
    pthread_mutex_unlock(&fbLock);
}



#endif