#pragma once
#include <string>
class UIAlertViewDelegateWraper{
public:
    UIAlertViewDelegateWraper(void){};
    ~UIAlertViewDelegateWraper(void){};
    virtual void clickedButtonAtIndex(int buttonIndex) = 0;
    virtual void alertViewCancel() = 0;
    virtual void willPresentAlertView() = 0;
    virtual void didPresentAlertView() = 0;
    virtual void willDismissWithButtonIndex(int buttonIndex) = 0;
    virtual void didDismissWithButtonIndex(int buttonIndex) = 0;
};
class UIAlertViewWraper {
public:
    UIAlertViewWraper(void);
    ~UIAlertViewWraper(void);
    static UIAlertViewWraper *getInstance();
    static void destroyInstance();
public:
    void initWithTitle(std::string title,std::string message,std::string cancel,std::string other,UIAlertViewDelegateWraper* delegate);
    void show();
};