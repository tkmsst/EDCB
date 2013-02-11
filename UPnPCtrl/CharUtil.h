#ifndef __MULTI_PLATFORM_CHAR_UTIL_H__
#define __MULTI_PLATFORM_CHAR_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

void MP_STR_Trim(char* src);

int MP_STR_CompNoCase(char* src1, char* src2);

int MP_STR_Separate(char* src, char* key, char* left, int leftSize, char* right, int rightSize);

int MP_STR_Replace(char* src, char* dest, int* destSize, char* oldStr, char* newStr);

void MP_TIME_GetNowTime_RFC1123(char* time, int timeSize);

#ifdef __cplusplus
}
#endif

#endif
