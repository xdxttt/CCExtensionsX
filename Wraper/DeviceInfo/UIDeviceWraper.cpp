#include "UIDeviceWraper.h"
UIDeviceWraper::UIDeviceWraper(void) {
}

UIDeviceWraper::~UIDeviceWraper(void) {
  
}

std::string  UIDeviceWraper::getUUID(){
#ifdef _WINDOWS
	return "0000000000000000000";
#else
	char temp[128]={0};
	long seconds= time((time_t*)NULL);
	sprintf(temp,"AD%ld/n",seconds);
	return temp;
#endif
}
std::string UIDeviceWraper::getUDID() {
#ifdef _WINDOWS
	return "0000000000000000000";
#else
	char temp[128]={0};
	long seconds= time((time_t*)NULL);
	sprintf(temp,"AD%ld/n",seconds);
	return temp;
#endif
}
std::string UIDeviceWraper::getName(){
	return "Win32";
}

std::string  UIDeviceWraper::getModel(){
	return "Win32";
}

std::string  UIDeviceWraper::getLocalizedModel(){
	return "getLocalizedModel";
}

std::string  UIDeviceWraper::getSystemName(){
	return "Win7";
}

std::string  UIDeviceWraper::getSystemVersion(){
	return "Win7";
}