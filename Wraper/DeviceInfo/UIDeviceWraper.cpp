#include "UIDeviceWraper.h"

UIDeviceWraper::UIDeviceWraper(void) {
}

UIDeviceWraper::~UIDeviceWraper(void) {

}

#ifndef _WIN32
#include "cocos2d.h"
#include "cocos/platform/android/jni/JniHelper.h"
#include <jni.h>
std::string  UIDeviceWraper::getUUID(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/cpp/UIDeviceWraper"
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
                                       , "org/cocos2dx/cpp/UIDeviceWraper"
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
                                       , "org/cocos2dx/cpp/UIDeviceWraper"
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
                                       , "org/cocos2dx/cpp/UIDeviceWraper"
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
                                       , "org/cocos2dx/cpp/UIDeviceWraper"
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
                                       , "org/cocos2dx/cpp/UIDeviceWraper"
                                       , "getSystemName"
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
    return std::string("UnknowSystemName");
}

std::string  UIDeviceWraper::getSystemVersion(){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                       , "org/cocos2dx/cpp/UIDeviceWraper"
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
#else
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
