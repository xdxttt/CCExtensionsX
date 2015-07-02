#include "AppInfo.h"
#if(CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
AppInfo::AppInfo(void) {
}

AppInfo::~AppInfo(void) {
}

std::string AppInfo::getVersion()
{
	return "0000";
}

std::string AppInfo::getBuild()
{
	return "Win32 Dev";
}
#endif