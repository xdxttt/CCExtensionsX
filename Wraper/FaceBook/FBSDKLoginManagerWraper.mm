//
//  FBSDKLoginManagerWraper.cpp
//  PuzzleWarrior
//
//  Created by xudexin on 15/5/5.
//
//

#include "FBSDKLoginManagerWraper.h"
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "NSErrorWraper.h"
#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>

FBSDKLoginManagerWraper*s_FBSDKLoginManagerWraper = NULL;
FBSDKLoginManagerListener *s_FBSDKLoginManagerListener = NULL;

FBSDKLoginManager *s_FBSDKLoginManager = NULL;
FBSDKProfileWraper* FBSDKProfileWraper::currentProfile(){
    FBSDKProfile * profile = [FBSDKProfile currentProfile];
    if (profile) {
        FBSDKProfileWraper *profileWraper = new FBSDKProfileWraper();
        if (profile.userID) {
            profileWraper->userID = [profile.userID cStringUsingEncoding:NSUTF8StringEncoding];
        }
        if (profile.firstName) {
            profileWraper->firstName = [profile.firstName cStringUsingEncoding:NSUTF8StringEncoding];
        }
        if (profile.middleName) {
            profileWraper->middleName = [profile.middleName cStringUsingEncoding:NSUTF8StringEncoding];
        }
        if (profile.lastName) {
            profileWraper->lastName = [profile.lastName cStringUsingEncoding:NSUTF8StringEncoding];
        }
        if (profile.name) {
            profileWraper->name = [profile.name cStringUsingEncoding:NSUTF8StringEncoding];
        }
        return profileWraper;
    }else{
        return  NULL;
    }
}
void FBSDKProfileWraper::enableUpdatesOnAccessTokenChange(bool enable){
    [FBSDKProfile enableUpdatesOnAccessTokenChange:(BOOL)enable];
}

FBSDKAccessTokenWraper* FBSDKAccessTokenWraper::currentAccessToken(){
    FBSDKAccessToken* token = [FBSDKAccessToken currentAccessToken];
    if(token){
        FBSDKAccessTokenWraper *tokenWraper = new FBSDKAccessTokenWraper();
        tokenWraper->appID = [token.appID cStringUsingEncoding:NSUTF8StringEncoding];
        tokenWraper->tokenString = [token.tokenString cStringUsingEncoding:NSUTF8StringEncoding];
        tokenWraper->userID = [token.userID cStringUsingEncoding:NSUTF8StringEncoding];
        for (NSString *value in [token.permissions objectEnumerator]) {
            tokenWraper->permissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        for (NSString *value in [token.declinedPermissions objectEnumerator]) {
            tokenWraper->declinedPermissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        return tokenWraper;
    }else{
        return  NULL;
    }
}
FBSDKLoginManagerWraper::FBSDKLoginManagerWraper(){
}
FBSDKLoginManagerWraper::~FBSDKLoginManagerWraper(){
}
FBSDKLoginManagerWraper* FBSDKLoginManagerWraper::getInstance(){
    if (s_FBSDKLoginManagerWraper==NULL) {
        s_FBSDKLoginManagerWraper = new FBSDKLoginManagerWraper();
        s_FBSDKLoginManager = [[FBSDKLoginManager alloc] init];
    }
    return s_FBSDKLoginManagerWraper;
}
void FBSDKLoginManagerWraper::destroyInstance(){
    if (s_FBSDKLoginManagerWraper) {
        delete s_FBSDKLoginManagerWraper;
        [s_FBSDKLoginManager release];
    }
}
void FBSDKLoginManagerWraper::update(){
}

void FBSDKLoginManagerWraper::logInWithPublishPermissions(std::set<std::string> permissions,FBSDKLoginManagerListener *listener){
    s_FBSDKLoginManagerListener = listener;
    
    NSMutableArray *permissionsArray = [[NSMutableArray alloc] initWithCapacity:permissions.size()];
    for (std::set<std::string>::iterator iter = permissions.begin(); iter!=permissions.end(); iter++) {
        NSString*permission = [[NSString alloc] initWithCString:(*iter).c_str() encoding:NSUTF8StringEncoding];
        [permissionsArray addObject:permission];
    }
    UIViewController * viewController = [[ [ UIApplication sharedApplication ] keyWindow] rootViewController];
    [s_FBSDKLoginManager logInWithPublishPermissions:permissionsArray fromViewController:viewController handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
        NSErrorWraper *err = NULL;
        FBSDKLoginManagerLoginResultWraper* resultWraper = NULL;
        if (error) {
            // Process error
            err = new NSErrorWraper();
            err->code = error.code;
            err->domain = [error.domain cStringUsingEncoding:NSUTF8StringEncoding];
        }
        
        if(result){
            resultWraper = new FBSDKLoginManagerLoginResultWraper();
            resultWraper->token = new FBSDKAccessTokenWraper();
            resultWraper->isCancelled = result.isCancelled;
            if(!resultWraper->isCancelled){
                [FBSDKAccessToken setCurrentAccessToken:result.token];
                for (NSString *value in [result.declinedPermissions objectEnumerator]) {
                    resultWraper->declinedPermissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
                }
                for (NSString *value in [result.grantedPermissions objectEnumerator]) {
                    resultWraper->grantedPermissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
                }
                resultWraper->token->appID = [result.token.appID cStringUsingEncoding:NSUTF8StringEncoding];
                resultWraper->token->tokenString = [result.token.tokenString cStringUsingEncoding:NSUTF8StringEncoding];
                resultWraper->token->userID = [result.token.userID cStringUsingEncoding:NSUTF8StringEncoding];
                for (NSString *value in [result.token.permissions objectEnumerator]) {
                    resultWraper->token->permissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
                }
                for (NSString *value in [result.token.declinedPermissions objectEnumerator]) {
                    resultWraper->token->declinedPermissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
                }
            }
        }
        if(err){
            s_FBSDKLoginManagerListener->onLogIn(resultWraper,err->domain.c_str());
        }else{
            s_FBSDKLoginManagerListener->onLogIn(resultWraper,NULL);
        }
    }];
}
void FBSDKLoginManagerWraper::logInWithReadPermissions(std::set<std::string> permissions,FBSDKLoginManagerListener *listener){
    s_FBSDKLoginManagerListener = listener;
    NSMutableArray *permissionsArray = [[NSMutableArray alloc] initWithCapacity:permissions.size()];
    for (std::set<std::string>::iterator iter = permissions.begin(); iter!=permissions.end(); iter++) {
        NSString*permission = [[NSString alloc] initWithCString:(*iter).c_str() encoding:NSUTF8StringEncoding];
        [permissionsArray addObject:permission];
    }
    UIViewController * viewController = [[ [ UIApplication sharedApplication ] keyWindow] rootViewController];
    [s_FBSDKLoginManager logInWithReadPermissions:permissionsArray fromViewController:viewController handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
     NSErrorWraper *err = NULL;
     FBSDKLoginManagerLoginResultWraper* resultWraper = NULL;
     if (error) {
     // Process error
     err = new NSErrorWraper();
     err->code = error.code;
     err->domain = [error.domain cStringUsingEncoding:NSUTF8StringEncoding];
     }
     
     if(result){
     resultWraper = new FBSDKLoginManagerLoginResultWraper();
     resultWraper->token = new FBSDKAccessTokenWraper();
     resultWraper->isCancelled = result.isCancelled;
     if(!resultWraper->isCancelled){
     for (NSString *value in [result.declinedPermissions objectEnumerator]) {
     resultWraper->declinedPermissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
     }
     for (NSString *value in [result.grantedPermissions objectEnumerator]) {
     resultWraper->grantedPermissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
     }
     resultWraper->token->appID = [result.token.appID cStringUsingEncoding:NSUTF8StringEncoding];
     resultWraper->token->tokenString = [result.token.tokenString cStringUsingEncoding:NSUTF8StringEncoding];
     resultWraper->token->userID = [result.token.userID cStringUsingEncoding:NSUTF8StringEncoding];
     for (NSString *value in [result.token.permissions objectEnumerator]) {
     resultWraper->token->permissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
     }
     for (NSString *value in [result.token.declinedPermissions objectEnumerator]) {
     resultWraper->token->declinedPermissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
     }
     }
     }
        if(err){
            s_FBSDKLoginManagerListener->onLogIn(resultWraper,err->domain.c_str());
        }else{
            s_FBSDKLoginManagerListener->onLogIn(resultWraper,NULL);
        }
     }];
}
#endif