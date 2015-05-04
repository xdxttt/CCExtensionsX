#pragma once
typedef std::function<void(std::string location)> ChartboostCallBack;
class ChartboostWapper{
public:
    ChartboostWapper(void);
    ~ChartboostWapper(void);
    static ChartboostWapper*getInstance();
    bool startWithAppId(std::string appid,std::string appSignature);
    bool hasAwardView();
    void showRewardedVideo(std::string location,const ChartboostCallBack &cb);
};