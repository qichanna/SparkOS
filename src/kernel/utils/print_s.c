#include "print_s.h"

#define va_start(args,format) args = (char *)&format;
#define va_arg(args,type) *((type*)(args+=4))
#define va_end(args) ((void)0)

char* number = {"0123456789ABCDEF"};

int print_s(char* format,...){
    char result[128];
    char* args;
    va_start(args,format);
    real_print(result,format,args);
    va_end(args);
    s_print(result);
    return 1;
}

int real_print(char* result,char* format,char* args){
    while (*format != '\0'){
        char c = *format;
        if(c != '%'){
            *(result++) = c;
        } else{
            c = *(++format);
            char* strs;
            int num;
            switch (c) {
                case 'c':
                    *(result++) = va_arg(args,char);
                    break;
                case 's':
                    strs = va_arg(args,char*);
                    strCopy(result,strs);
                    result += strToLong(strs);
                    break;
                case 'd':
                    num = va_arg(args,int);
                    numToStr(&result,num,10);
                    break;
                case 'x':
                    num = va_arg(args,int);
                    *result++ = '0';
                    *result++ = 'x';
                    numToStr(&result,num,16);
                    break;
                default:
                    break;
            }
        }
        format++;
    }
    return 1;
}

void numToStr(char** result,int arg,int base){
    if(arg < 0){
        *((*result)++) = '-';
        arg *= -1;
    }

    if(arg == 0)return;
    int position = arg / base;
    numToStr(result,position,base);
    int n = arg % base;
    *((*result)++) = number[n];
}