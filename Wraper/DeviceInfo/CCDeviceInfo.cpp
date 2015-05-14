#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h> 
#include <iostream> 
#include <conio.h> 
char mac_addr[18];
#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)



CCDeviceInfo::CCDeviceInfo(void) {
}

CCDeviceInfo::~CCDeviceInfo(void) {
}

std::string CCDeviceInfo::getUDID() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	GUID guid; 
	CoCreateGuid(&guid); 
	char buf[64] = {0};
	snprintf(
		buf,
		sizeof(buf),
		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return std::string(buf);
#endif // #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return "TEMPANDROIDAAA";
}
std::string CCDeviceInfo::getName()
{
	return "Windows Simulator";

}

std::string CCDeviceInfo::getModel()
{
	return "Windows Simulator";
}

std::string CCDeviceInfo::getLocalizedModel()
{
	return "Windows Simulator";
}

std::string CCDeviceInfo::getSystemName()
{
	return "Windows 7";
}

std::string CCDeviceInfo::getSystemVersion()
{
	return "Windows 7";
}

std::string CCDeviceInfo::getUUID()
{
	return "";
}

std::string CCDeviceInfo::getDefaultLanguage()
{
	return "cn";
}
