#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "UIAlertViewWraper.h"
#include "UIAlertViewWraperImp.h"
UIAlertViewWraper *g_UIAlertViewWraper = NULL;
UIAlertViewDelegateWraper *g_UIAlertViewDelegateWraper = NULL;
UIAlertViewDelegateImp *g_UIAlertViewDelegateImp = NULL;
UIAlertView *g_UIAlertView = NULL;

UIAlertViewWraper::UIAlertViewWraper(){
}
UIAlertViewWraper::~UIAlertViewWraper(){
}
void UIAlertViewWraper::destroyInstance()
{
    if (g_UIAlertViewWraper) {
        delete g_UIAlertViewWraper;
    }
    if (g_UIAlertViewDelegateImp) {
        [g_UIAlertViewDelegateImp release];
    }
}

UIAlertViewWraper* UIAlertViewWraper::getInstance()
{
    if (g_UIAlertViewWraper == NULL) {
        g_UIAlertViewWraper = new UIAlertViewWraper();
    }
    if (g_UIAlertViewDelegateImp == NULL) {
        g_UIAlertViewDelegateImp = [UIAlertViewDelegateImp alloc];
    }
    return g_UIAlertViewWraper;
}

void UIAlertViewWraper::initWithTitle(std::string title,std::string message,std::string cancel,std::string other,UIAlertViewDelegateWraper* delegate){
    g_UIAlertViewDelegateWraper = delegate;
    NSString *nstitle = [[[NSString alloc] initWithCString:title.c_str() encoding:NSUTF8StringEncoding] autorelease];
    NSString *nsmessage = [[[NSString alloc] initWithCString:message.c_str() encoding:NSUTF8StringEncoding] autorelease];
    NSString *nscancel = [[[NSString alloc] initWithCString:cancel.c_str() encoding:NSUTF8StringEncoding] autorelease];
    NSString *nsother = [[[NSString alloc] initWithCString:other.c_str() encoding:NSUTF8StringEncoding] autorelease];
    g_UIAlertView = [[UIAlertView alloc] initWithTitle:nstitle
                                               message:nsmessage
                                              delegate:g_UIAlertViewDelegateImp
                                     cancelButtonTitle:nscancel otherButtonTitles:nsother, nil];
}

void UIAlertViewWraper::show(){
    [g_UIAlertView show];
}
