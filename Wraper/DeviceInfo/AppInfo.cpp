#include "AppInfo.h"
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