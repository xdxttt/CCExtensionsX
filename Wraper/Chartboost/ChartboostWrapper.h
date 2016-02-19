#pragma once

//TODO change TO Virtul Class
typedef std::function<void(std::string location)> ChartboostDelegateWrapper;

class ChartboostWrapper{
public:
    ChartboostWrapper(void);
    ~ChartboostWrapper(void);
    static ChartboostWrapper*getInstance();
    bool startWithAppId(std::string appid,std::string appSignature);
    bool hasAwardView();
    void showRewardedVideo(std::string location,const ChartboostDelegateWrapper &delegate);
};