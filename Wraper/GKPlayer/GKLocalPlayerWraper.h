#pragma once
#include "NSErrorWraper.h"
class GKPlayerWraper{
public:
    GKPlayerWraper();
    ~GKPlayerWraper();
    bool authenticated;
    std::string playerID;
    std::string alias;
};
typedef std::function<void(NSErrorWraper* error)> AuthenticateWithCompletionHandler;
class GKLocalPlayerWraper{
public:
    static GKLocalPlayerWraper *getInstance();
    static void destroyInstance();
public:
    GKLocalPlayerWraper();
    ~GKLocalPlayerWraper();
    void authenticateWithCompletionHandler(const AuthenticateWithCompletionHandler &hd);
    GKPlayerWraper m_localPlayer;
};
