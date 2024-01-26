#include <stdio.h>
#include <stdlib.h>

int main()
{
    const char *ptr = "12abc12"; 
    #if 0
    int value = atoi(ptr);
    #elif 0
    long value = 0;
    int len = sizeof(value);
    printf("len:%d\n", len);
    #else
    char *endptr = NULL;
    int value = strtol(ptr, &endptr, 0);

    printf("value:%d,\t value:%o\t endptr:%s\n", value, value, endptr);
    

    #endif



}