#include "ChartboostWrapper.h"
#import <Foundation/Foundation.h>
#import <Chartboost/Chartboost.h>

@interface ChartboostDelegateImp : NSObject <ChartboostDelegate>
{
}
@end


ChartboostWrapper* s_SharedChartboostWrapper = NULL;
ChartboostDelegateImp* s_ChartboostDelegateImp = NULL;
ChartboostDelegateWrapper s_ChartboostDelegate = NULL;

@implementation ChartboostDelegateImp
#pragma mark -
#pragma mark ChartboostDelegateImp methods
- (BOOL)shouldRequestInterstitial:(CBLocation)location{
    return true;
}

- (BOOL)shouldDisplayInterstitial:(CBLocation)location{
    return true;
}

- (void)didDisplayInterstitial:(CBLocation)location{
    
}

- (void)didCacheInterstitial:(CBLocation)location{
    
}

- (void)didFailToLoadInterstitial:(CBLocation)location
                        withError:(CBLoadError)error{
    
}

- (void)didFailToRecordClick:(CBLocation)location
                   withError:(CBClickError)error{
    
}

- (void)didDismissInterstitial:(CBLocation)location{
    
}

- (void)didCloseInterstitial:(CBLocation)location{
    
}

- (void)didClickInterstitial:(CBLocation)location{
    
}

- (BOOL)shouldDisplayMoreApps:(CBLocation)location{
    return true;
    
}

- (void)didDisplayMoreApps:(CBLocation)location{
}

- (void)didCacheMoreApps:(CBLocation)location{
    
}

- (void)didDismissMoreApps:(CBLocation)location{
    
}

- (void)didCloseMoreApps:(CBLocation)location{
    
}

- (void)didClickMoreApps:(CBLocation)location{
    
}

- (void)didFailToLoadMoreApps:(CBLocation)location
                    withError:(CBLoadError)error{
    
}
#pragma mark - Video Delegate

- (void)didPrefetchVideos{
    
}
#pragma mark - Rewarded Video Delegate

- (BOOL)shouldDisplayRewardedVideo:(CBLocation)location{
    return true;
}

- (void)didDisplayRewardedVideo:(CBLocation)location{
    
}
- (void)didCacheRewardedVideo:(CBLocation)location{
    
}
- (void)didFailToLoadRewardedVideo:(CBLocation)location
                         withError:(CBLoadError)error{
    
}
- (void)didDismissRewardedVideo:(CBLocation)location{
    
}
- (void)didCloseRewardedVideo:(CBLocation)location{
    
}
- (void)didClickRewardedVideo:(CBLocation)location{
    
}
- (void)didCompleteRewardedVideo:(CBLocation)location
                      withReward:(int)reward{
    if (s_ChartboostDelegate) {
        s_ChartboostDelegate([location UTF8String]);
    }
}
#pragma mark - InPlay Delegate
- (void)didCacheInPlay:(CBLocation)location{
    
}
- (void)didFailToLoadInPlay:(CBLocation)location
                  withError:(CBLoadError)error{
    
}
#pragma mark - General Delegate
- (void)willDisplayVideo:(CBLocation)location{
    
}
- (void)didCompleteAppStoreSheetFlow{
    
}
- (void)didPauseClickForConfirmation{
    
}
@end

ChartboostWrapper::ChartboostWrapper(){

}
ChartboostWrapper::~ChartboostWrapper(){
    
}
ChartboostWrapper* ChartboostWrapper::getInstance() {
    if (!s_SharedChartboostWrapper) {
        s_SharedChartboostWrapper = new ChartboostWrapper();
    }
    if (!s_ChartboostDelegateImp) {
        s_ChartboostDelegateImp = [ChartboostDelegateImp alloc];
    }
    return s_SharedChartboostWrapper;
}
bool ChartboostWrapper::startWithAppId(std::string appid,std::string appSignature ){
    NSString *nssAppid = [[[NSString alloc] initWithCString:appid.c_str() encoding:NSUTF8StringEncoding] autorelease];
    NSString *nssAppSignature = [[[NSString alloc] initWithCString:appSignature.c_str() encoding:NSUTF8StringEncoding] autorelease];
    [Chartboost startWithAppId:nssAppid appSignature:nssAppSignature delegate:s_ChartboostDelegateImp];
    [Chartboost cacheRewardedVideo:CBLocationMainMenu];
    [Chartboost cacheMoreApps:CBLocationHomeScreen];
    return true;
}
bool ChartboostWrapper::hasAwardView(){
    return [Chartboost hasRewardedVideo:CBLocationMainMenu];
}
void ChartboostWrapper::showRewardedVideo(std::string location,const ChartboostDelegateWrapper &cb){
    s_ChartboostDelegate = cb;
    NSString *loc = [[[NSString alloc] initWithCString:location.c_str() encoding:NSUTF8StringEncoding] autorelease];
    [Chartboost showRewardedVideo:loc];
}