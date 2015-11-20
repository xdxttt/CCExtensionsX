#include "AppInfo.h"
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos/platform/android/jni/JniHelper.h"
#include <jni.h>
AppInfo::AppInfo(void) {
}

AppInfo::~AppInfo(void) {
}
std::string AppInfo::getVersion()
{
   cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "com/malom/ccextensions/AppInfo"
                                       , "getVersion"
                                       , "()Ljava/lang/String;"))
    {
        jstring jstr = NULL;
        jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        char* cstr = NULL;
        cstr = (char*) t.env->GetStringUTFChars(jstr, 0);
        std::string ret(cstr);
        t.env->ReleaseStringUTFChars(jstr, cstr);
        t.env->DeleteLocalRef(jstr);
        return ret.c_str();
    }
    return std::string("UnknowVersion");
}
std::string AppInfo::getBuild()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                      , "com/malom/ccextensions/AppInfo"
                                       , "getBuild"
                                       , "()Ljava/lang/String;"))
    {
        jstring jstr = NULL;
        jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        char* cstr = NULL;
        cstr = (char*) t.env->GetStringUTFChars(jstr, 0);
        std::string ret(cstr);
        t.env->ReleaseStringUTFChars(jstr, cstr);
        t.env->DeleteLocalRef(jstr);
        return ret.c_str();
    }
    return std::string("UnknowBuild");
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
std::string AppInfo::getVersion()
{
	return std::string("WindowsVersion");
}
std::string AppInfo::getBuild()
{
	return std::string("DevBuild");
}
#endif
