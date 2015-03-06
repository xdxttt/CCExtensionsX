//
//  Crypto.cpp
//
//  Created by xudexin on 13-5-11.
//
//

#include "Crypto.h"
#include "md5.h"

Crypto* sCrypto = NULL;

Crypto *Crypto::getInstance(){
    if (sCrypto==NULL) {
        sCrypto = new Crypto;
    }
    return sCrypto;
}
void Crypto::destroyInstance(){
    if (sCrypto) {
        delete sCrypto;
    }
}
Crypto::Crypto(){
    
}
Crypto::~Crypto(){
    
}

std::string Crypto::md5(const char *src, int len){
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