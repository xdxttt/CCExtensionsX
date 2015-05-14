#pragma once


class FBSDKGameRequestContentWraper{
public:
    FBSDKGameRequestContentWraper();
    ~FBSDKGameRequestContentWraper();

    //FBSDKGameRequestActionType actionType;
//    - (BOOL)isEqualToGameRequestContent:(FBSDKGameRequestContent *)content;
    std::string data;
   // FBSDKGameRequestFilter filters;
    std::string message;
    std::string objectID;
    std::set<std::string> to;
    std::set<std::string> suggestions;
    std::string title;
};
//typedef std::function<void(FBSDKLoginManagerLoginResultWraper* result,NSErrorWraper* error)> LogInWithReadPermissionsHandler;
class FBSDKGameRequestDialogWraper{
public:
    FBSDKGameRequestDialogWraper();
    ~FBSDKGameRequestDialogWraper();
    static FBSDKGameRequestDialogWraper *getInstance();
    static void destroyInstance();
    void showWithContent();
};