//
//  Crypto.cpp
//
//  Created by xudexin on 13-5-11.
//
//

#include "Crypto.h"
#include "md5.h"

CCCrypto* sCCCrypto = NULL;

CCCrypto *CCCrypto::getInstance(){
    if (sCCCrypto==NULL) {
        sCCCrypto = new CCCrypto;
    }
    return sCCCrypto;
}
void CCCrypto::destroyInstance(){
    if (sCCCrypto) {
        delete sCCCrypto;
    }
}
CCCrypto::CCCrypto(){
    
}
CCCrypto::~CCCrypto(){
    
}

std::string CCCrypto::md5(const char *src, int len){
    unsigned char output[256]={0};
    std::string ret;
    
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, (void*)src,len);
    MD5_Final((unsigned char *)&output, &ctx);
    for (int i=0; i<16; i++) {
        char temp[32] = {0};
        sprintf(temp,"%02x",output[i]);
        ret.append(temp);
    }

    return ret;
}