#include "GKLocalPlayerWraper.h"
#include <GameKit/GameKit.h>

GKLocalPlayerWraper *s_GKLocalPlayerWraper = NULL;
AuthenticateWithCompletionHandler s_hd;
GKLocalPlayer *s_localPlayer = NULL;

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
    s_hd = hd;
        [s_localPlayer authenticateWithCompletionHandler:^(NSError *error){
        if (error == nil) {
            m_localPlayer.alias = [[GKLocalPlayer localPlayer].alias cStringUsingEncoding:NSUTF8StringEncoding];
            m_localPlayer.playerID = [[GKLocalPlayer localPlayer].playerID cStringUsingEncoding:NSUTF8StringEncoding];
            m_localPlayer.authenticated = [GKLocalPlayer localPlayer].authenticated;
            s_hd(NULL);
        }else {
            NSErrorWraper err;
            err.code = [error code];
            err.domain = [[error domain] cStringUsingEncoding:NSUTF8StringEncoding];
            NSLog(@"失败  %@",error);
        }
    }];
}