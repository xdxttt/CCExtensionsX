//
//  Chartboost.cpp
//  PuzzleWarrior
//
//  Created by xudexin on 15/4/29.
//
//

#include "ChartboostWapper.h"
#include "ChartboostDelegateImp.h"
ChartboostWapper* s_SharedChartboostWapper = NULL;
ChartboostDelegateImp* s_ChartboostDelegateImp = NULL;

ChartboostCallBack s_ShowRewardedVideoCallBack = NULL;
ChartboostWapper::ChartboostWapper(){

}
ChartboostWapper::~ChartboostWapper(){
    
}
ChartboostWapper* ChartboostWapper::getInstance() {
    if (!s_SharedChartboostWapper) {
        s_SharedChartboostWapper = new ChartboostWapper();
    }
    if (!s_ChartboostDelegateImp) {
        s_ChartboostDelegateImp = [ChartboostDelegateImp alloc];
    }
    return s_SharedChartboostWapper;
}
bool ChartboostWapper::startWithAppId(std::string appid,std::string appSignature ){
    NSString *nssAppid = [[[NSString alloc] initWithCString:appid.c_str() encoding:NSUTF8StringEncoding] autorelease];
    NSString *nssAppSignature = [[[NSString alloc] initWithCString:appSignature.c_str() encoding:NSUTF8StringEncoding] autorelease];
    [Chartboost startWithAppId:nssAppid appSignature:nssAppSignature delegate:s_ChartboostDelegateImp];
    [Chartboost cacheRewardedVideo:CBLocationMainMenu];
    [Chartboost cacheMoreApps:CBLocationHomeScreen];
    return true;
}
bool ChartboostWapper::hasAwardView(){
    return [Chartboost hasRewardedVideo:CBLocationMainMenu];
}
void ChartboostWapper::showRewardedVideo(std::string location,const ChartboostCallBack &cb){
    s_ShowRewardedVideoCallBack = cb;
    [Chartboost showRewardedVideo:@""];
}