#pragma once
#include <string>
class UIDeviceWraper {
public:
	UIDeviceWraper(void);
	~UIDeviceWraper(void);
    
	static std::string getUDID();
    static std::string getName();
    static std::string getModel();
    static std::string getLocalizedModel();
    static std::string getSystemName();
    static std::string getSystemVersion();
    static std::string getUUID();
	static std::string getDefaultLanguage();
};