#pragma once
#include <string>
class AppInfo {
public:
	AppInfo(void);
	~AppInfo(void);
	static std::string getVersion();
	static std::string getBuild();
};