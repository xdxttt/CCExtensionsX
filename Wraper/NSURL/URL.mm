#include "URL.h"
void openUrl(std::string url){
    NSString *nsstring = [[[NSString alloc] initWithCString:url.c_str() encoding:NSUTF8StringEncoding] autorelease];
    NSURL * nsurl = [NSURL URLWithString:nsstring];
    [[UIApplication sharedApplication] openURL: nsurl];
}