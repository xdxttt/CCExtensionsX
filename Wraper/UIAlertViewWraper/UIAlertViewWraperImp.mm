#import <Foundation/Foundation.h>
#include "UIAlertViewWraper.h"
#import "UIAlertViewWraperImp.h"

extern UIAlertViewDelegateWraper *g_UIAlertViewDelegateWraper;

@implementation UIAlertViewDelegateImp
#pragma mark  -- UIAlertViewDelegate --
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    g_UIAlertViewDelegateWraper->clickedButtonAtIndex((int)buttonIndex);
}
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    g_UIAlertViewDelegateWraper->didDismissWithButtonIndex((int)buttonIndex);
}
- (void)alertView:(UIAlertView *)alertView willDismissWithButtonIndex:(NSInteger)buttonIndex {
    g_UIAlertViewDelegateWraper->willDismissWithButtonIndex((int)buttonIndex);
}
- (void)alertViewCancel:(UIAlertView *)alertView {
    g_UIAlertViewDelegateWraper->alertViewCancel();
}
- (void)didPresentAlertView:(UIAlertView *)alertView {
    g_UIAlertViewDelegateWraper->didPresentAlertView();
}
- (void)willPresentAlertView:(UIAlertView *)alertView {
    g_UIAlertViewDelegateWraper->willPresentAlertView();
}
@end