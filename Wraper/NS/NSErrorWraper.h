#pragma once
class NSErrorWraper{
public:
    NSErrorWraper(){}
    ~NSErrorWraper(){}
    long code;
    std::string domain;
    //NSDictionary *_userInfo;
};