#include "AppsFlyerTrackerWraper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos2d.h"
#include "cocos/platform/android/jni/JniHelper.h"
#include <jni.h>

AppsFlyerTrackerWraper *s_AppsFlyerTrackerWraper = NULL;

AppsFlyerTrackerWraper::AppsFlyerTrackerWraper(){
}
AppsFlyerTrackerWraper::~AppsFlyerTrackerWraper(){
}
void AppsFlyerTrackerWraper::destroyInstance()
{
    if (s_AppsFlyerTrackerWraper) {
        delete s_AppsFlyerTrackerWraper;
    }
}
AppsFlyerTrackerWraper* AppsFlyerTrackerWraper::getInstance()
{
    if (s_AppsFlyerTrackerWraper == NULL) {
        s_AppsFlyerTrackerWraper = new AppsFlyerTrackerWraper();
    }
    return s_AppsFlyerTrackerWraper;
}

//void AppsFlyerTrackerWraper::trackEvent(std::string event,std::string value){
//       cocos2d::JniMethodInfo t;
//    if (cocos2d::JniHelper::getStaticMethodInfo(t
//                                                , "com/malom/ccextensions/AppsFlyerWraper"
//                                                , "sendTrackingWithEvent"
//                                                , "(Ljava/lang/String;Ljava/lang/String;)V"))
//    {
//        CCLOG("AppsFlyerTrackerWraper::sendTrackingWithEvent");
//        jstring jevent = t.env->NewStringUTF(event.c_str());
//        jstring jvalue = t.env->NewStringUTF(value.c_str());
//        t.env->CallStaticVoidMethod(t.classID,t.methodID,jevent,jvalue);
//    }
//}
void AppsFlyerTrackerWraper::trackEvent(std::string event,std::map<std::string,std::string> values){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , "com/malom/ccextensions/AppsFlyerWraper"
                                                , "trackEvent"
                                                , "(Ljava/lang/String;Ljava/util/Map;)V"))
    {
        CCLOG("AppsFlyerTrackerWraper::trackEvents");
        jstring jevent = t.env->NewStringUTF(event.c_str());
        jclass jmap = t.env->FindClass("java/util/HashMap");
        jmethodID jmap_init = t.env->GetMethodID(jmap, "<init>", "()V");
        jmethodID jmap_put = t.env->GetMethodID(jmap, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
        jobject jevents = t.env->NewObject(jmap, jmap_init);
        
        for (std::map<std::string,std::string>::iterator iter = values.begin(); iter != values.end(); iter++) {
            t.env->CallObjectMethod(jevents, jmap_put, t.env->NewStringUTF(iter->first.c_str()),t.env->NewStringUTF(iter->first.c_str()));
        }
        t.env->CallStaticVoidMethod(t.classID,t.methodID,jevent,jevents);
    }
}

#endif

