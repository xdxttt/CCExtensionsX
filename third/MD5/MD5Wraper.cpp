//
//  MD5Wraper.cpp
//  PuzzleWarrior
//
//  Created by xudexin on 15/5/5.
//
//

#include "MD5Wraper.h"
#include "md5.h"
std::string MD5(const char *src, size_t len){
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