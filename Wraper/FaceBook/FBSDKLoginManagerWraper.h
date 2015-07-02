#pragma once
#include <set>
#include "NSErrorWraper.h"

class FBSDKProfileWraper{
public:
    FBSDKProfileWraper(){};
    ~FBSDKProfileWraper(){};
    static FBSDKProfileWraper* currentProfile();
    std::string userID;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string name;
    static void enableUpdatesOnAccessTokenChange(bool enable);
};


class FBSDKAccessTokenWraper{
public:
    FBSDKAccessTokenWraper(){};
    ~FBSDKAccessTokenWraper(){};
    std::string appID;
    std::set<std::string> declinedPermissions;
    std::set<std::string> permissions;
    char refreshDate[1024];
    char expirationDate[1024];
    std::string tokenString;
    std::string userID;
    static FBSDKAccessTokenWraper* currentAccessToken();
};
class FBSDKLoginManagerLoginResultWraper{
public:
    FBSDKLoginManagerLoginResultWraper(){};
    ~FBSDKLoginManagerLoginResultWraper(){};
    FBSDKAccessTokenWraper *token;
    bool isCancelled;
    std::set<std::string> grantedPermissions;
    std::set<std::string> declinedPermissions;
};

typedef std::function<void(FBSDKLoginManagerLoginResultWraper* result,NSErrorWraper* error)> LogInWithReadPermissionsHandler;

class FBSDKLoginManagerWraper{
public:
    FBSDKLoginManagerWraper();
    ~FBSDKLoginManagerWraper();
    static FBSDKLoginManagerWraper *getInstance();
    static void destroyInstance();
    void logInWithReadPermissions(std::set<std::string> permissions,const LogInWithReadPermissionsHandler &hd);
    void logInWithPublishPermissions(std::set<std::string> permissions,const LogInWithReadPermissionsHandler &hd);
    
};