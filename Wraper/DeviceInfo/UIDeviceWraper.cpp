#include "UIDeviceWraper.h"
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos/platform/android/jni/JniHelper.h"
#include <jni.h>

UIDeviceWraper::UIDeviceWraper(void) {
}

UIDeviceWraper::~UIDeviceWraper(void) {
    
}
std::string UIDeviceWraper::getDeviceType(){
    return std::string("A");
}
std::string  UIDeviceWraper::getUUID(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "com/malom/ccextensions/UIDeviceWraper"
                                       , "getUUID"
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
    return std::string("UnknowUUID");
}

std::string UIDeviceWraper::getUDID() {
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "com/malom/ccextensions/UIDeviceWraper"
                                               , "getUDID"
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
    return std::string("UnknowUDID");
 }

std::string UIDeviceWraper::getName(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "com/malom/ccextensions/UIDeviceWraper"
                                       , "getName"
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
    return std::string("UnknowName");
}
std::string  UIDeviceWraper::getModel(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "com/malom/ccextensions/UIDeviceWraper"
                                       , "getModel"
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
    return std::string("UnknowModel");
}

std::string  UIDeviceWraper::getLocalizedModel(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "com/malom/ccextensions/UIDeviceWraper"
                                       , "getLocalizedModel"
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
    return std::string("UnknowModel");
}

std::string  UIDeviceWraper::getSystemName(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "com/malom/ccextensions/UIDeviceWraper"
                                       , "getSystemName"
                                       , "()Ljava/lang/String;"))
    {
        jstring jstr = NULL;
        jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        std::string ret = cocos2d::JniHelper::jstring2string(jstr);
        t.env->DeleteLocalRef(jstr);
        t.env->DeleteLocalRef(t.classID);

        return ret;
    }
    return std::string("UnknowSystemName");
}

std::string  UIDeviceWraper::getSystemVersion(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "com/malom/ccextensions/UIDeviceWraper"
                                       , "getSystemVersion"
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
    return std::string("UnknowSystemVersion");
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

UIDeviceWraper::UIDeviceWraper(void) {
}

UIDeviceWraper::~UIDeviceWraper(void) {
    
}

std::string  UIDeviceWraper::getUUID(){
	return std::string("00000000000000000001");
}

std::string UIDeviceWraper::getUDID() {
	return std::string("00000000000000000001");
}

std::string UIDeviceWraper::getName(){
	return std::string("UnknowName");
}
std::string  UIDeviceWraper::getModel(){
	return std::string("UnknowModel");
}

std::string  UIDeviceWraper::getLocalizedModel(){
	return std::string("UnknowModel");
}

std::string  UIDeviceWraper::getSystemName(){
	return std::string("UnknowSystemName");
}

std::string  UIDeviceWraper::getSystemVersion(){
	return std::string("UnknowSystemVersion");
}
#endif
