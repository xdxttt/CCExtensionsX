#include "AppInfo.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
AppInfo::AppInfo(void) {
}

AppInfo::~AppInfo(void) {
}
std::string AppInfo::getVersion() {
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    NSString *version = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
    return [version cStringUsingEncoding: NSUTF8StringEncoding];
}
std::string AppInfo::getBuild() {
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    NSString *build = [infoDictionary objectForKey:@"CFBundleVersion"];
    return [build cStringUsingEncoding: NSUTF8StringEncoding];
}
#endif