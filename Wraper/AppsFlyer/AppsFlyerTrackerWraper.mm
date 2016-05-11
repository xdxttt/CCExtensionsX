#include "AppsFlyerTrackerWraper.h"
#include <AppsFlyerTracker.h>

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
//    NSString *nsevent = [[[NSString alloc] initWithCString:event.c_str() encoding:NSUTF8StringEncoding] autorelease];
//    NSString *nsvalue = [[[NSString alloc] initWithCString:value.c_str() encoding:NSUTF8StringEncoding] autorelease];
//    [[AppsFlyerTracker sharedTracker]trackEvent:nsevent withValue:nsvalue];
//}
void AppsFlyerTrackerWraper::trackEvent(std::string event,std::map<std::string,std::string> values){
    NSString *nsevent = [[[NSString alloc] initWithCString:event.c_str() encoding:NSUTF8StringEncoding] autorelease];
    
    NSMutableDictionary *nsdict = [[NSMutableDictionary alloc] init];
    for (std::map<std::string,std::string>::iterator iter = values.begin(); iter!=values.end(); iter++) {
        NSString*key = [[NSString alloc] initWithCString:(iter->first).c_str() encoding:NSUTF8StringEncoding];
        NSString*value = [[NSString alloc] initWithCString:(iter->second).c_str() encoding:NSUTF8StringEncoding];
       [nsdict setValue:value forKey:key];
    }
    [[AppsFlyerTracker sharedTracker]trackEvent:nsevent withValues:nsdict];
}



