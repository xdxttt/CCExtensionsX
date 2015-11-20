#include "UIAlertViewWraper.h"
UIAlertViewWraper *g_UIAlertViewWraper = NULL;
UIAlertViewWraper::UIAlertViewWraper(){
}
UIAlertViewWraper::~UIAlertViewWraper(){
}
void UIAlertViewWraper::destroyInstance()
{
    if (g_UIAlertViewWraper) {
        delete g_UIAlertViewWraper;
    }
}

UIAlertViewWraper* UIAlertViewWraper::getInstance()
{
    if (g_UIAlertViewWraper == NULL) {
        g_UIAlertViewWraper = new UIAlertViewWraper();
    }
    return g_UIAlertViewWraper;
}

void UIAlertViewWraper::initWithTitle(std::string title,std::string message,std::string cancel,std::string other,UIAlertViewDelegateWraper* delegate){
}

void UIAlertViewWraper::show(){
}
