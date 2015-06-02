//
//  FBSDKLoginManagerWraper.cpp
//  PuzzleWarrior
//
//  Created by xudexin on 15/5/5.
//
//

#include "FBSDKLoginManagerWraper.h"
#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FBSDKLoginKit/FBSDKLoginKit.h>

FBSDKLoginManagerWraper*s_FBSDKLoginManagerWraper = NULL;
FBSDKLoginManager *s_FBSDKLoginManager = NULL;
LogInWithReadPermissionsHandler s_LogInWithReadPermissionsHandler;
FBSDKAccessTokenWraper* s_tokenWraper = NULL;

FBSDKAccessTokenWraper* FBSDKAccessTokenWraper::currentAccessToken(){
    FBSDKAccessToken* token = [FBSDKAccessToken currentAccessToken];
    if(token){
        if (s_tokenWraper==NULL) {
            s_tokenWraper = new FBSDKAccessTokenWraper();
        }
        s_tokenWraper->appID = [token.appID cStringUsingEncoding:NSUTF8StringEncoding];
        s_tokenWraper->tokenString = [token.tokenString cStringUsingEncoding:NSUTF8StringEncoding];
        s_tokenWraper->userID = [token.userID cStringUsingEncoding:NSUTF8StringEncoding];
        for (NSString *value in [token.permissions objectEnumerator]) {
            s_tokenWraper->permissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        for (NSString *value in [token.declinedPermissions objectEnumerator]) {
            s_tokenWraper->declinedPermissions.insert([value cStringUsingEncoding:NSUTF8StringEncoding]);
        }
        return s_tokenWraper;
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
void FBSDKLoginManagerWraper::logInWithPublishPermissions(std::set<std::string> permissions,const LogInWithReadPermissionsHandler &hd){
    s_LogInWithReadPermissionsHandler = hd;
    
    NSMutableArray *permissionsArray = [[NSMutableArray alloc] initWithCapacity:permissions.size()];
    for (std::set<std::string>::iterator iter = permissions.begin(); iter!=permissions.end(); iter++) {
        NSString*permission = [[NSString alloc] initWithCString:(*iter).c_str() encoding:NSUTF8StringEncoding];
        [permissionsArray addObject:permission];
    }
    
    [s_FBSDKLoginManager logInWithPublishPermissions:permissionsArray handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
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
        s_LogInWithReadPermissionsHandler(resultWraper,err);
    }];
}
void FBSDKLoginManagerWraper::logInWithReadPermissions(std::set<std::string> permissions,const LogInWithReadPermissionsHandler &hd){
    s_LogInWithReadPermissionsHandler = hd;
    NSMutableArray *permissionsArray = [[NSMutableArray alloc] initWithCapacity:permissions.size()];
    for (std::set<std::string>::iterator iter = permissions.begin(); iter!=permissions.end(); iter++) {
        NSString*permission = [[NSString alloc] initWithCString:(*iter).c_str() encoding:NSUTF8StringEncoding];
        [permissionsArray addObject:permission];
    }
    [s_FBSDKLoginManager logInWithReadPermissions:permissionsArray handler:^(FBSDKLoginManagerLoginResult *result, NSError *error) {
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
     s_LogInWithReadPermissionsHandler(resultWraper,err);
     }];
}