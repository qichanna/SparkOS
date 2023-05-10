#include "stringUtils.h"

int strToLong(char* str){
    int count = 0;
    while (*str++ != '\0') count++;
    return count;
}

void strCopy(char* dst,char* src){
    while (*src != '\0'){
        *(dst++) = *(src++);
    }
}