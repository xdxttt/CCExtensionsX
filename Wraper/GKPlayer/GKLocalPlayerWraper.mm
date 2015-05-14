#include "GKLocalPlayerWraper.h"
#include <GameKit/GameKit.h>

GKLocalPlayerWraper *s_GKLocalPlayerWraper = NULL;
GKLocalPlayer *s_localPlayer = NULL;
AuthenticateWithCompletionHandler  s_AuthenticateWithCompletionHandler;
GKPlayerWraper::GKPlayerWraper(){
    authenticated = false;
}
GKPlayerWraper::~GKPlayerWraper(){
}
GKLocalPlayerWraper::GKLocalPlayerWraper(){
}
GKLocalPlayerWraper::~GKLocalPlayerWraper(){
}
void GKLocalPlayerWraper::destroyInstance()
{
    if (s_GKLocalPlayerWraper) {
        delete s_GKLocalPlayerWraper;
    }
    if (s_localPlayer) {
        [s_localPlayer release];
    }
}

GKLocalPlayerWraper* GKLocalPlayerWraper::getInstance()
{
    if (s_GKLocalPlayerWraper == NULL) {
        s_GKLocalPlayerWraper = new GKLocalPlayerWraper();
        s_localPlayer = [GKLocalPlayer localPlayer];
    }
    return s_GKLocalPlayerWraper;
}
void GKLocalPlayerWraper::authenticateWithCompletionHandler(const AuthenticateWithCompletionHandler &hd){
    s_AuthenticateWithCompletionHandler = hd;
        [s_localPlayer authenticateWithCompletionHandler:^(NSError *error){
        if (error == nil) {
            m_localPlayer.alias = [[GKLocalPlayer localPlayer].alias cStringUsingEncoding:NSUTF8StringEncoding];
            m_localPlayer.playerID = [[GKLocalPlayer localPlayer].playerID cStringUsingEncoding:NSUTF8StringEncoding];
            m_localPlayer.authenticated = [GKLocalPlayer localPlayer].authenticated;
            s_AuthenticateWithCompletionHandler(NULL);
        }else {
            NSErrorWraper err;
            err.code = [error code];
            err.domain = [[error domain] cStringUsingEncoding:NSUTF8StringEncoding];
            s_AuthenticateWithCompletionHandler(&err);
        }
    }];
}