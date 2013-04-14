#ifndef __OAUTH_UTIL_H__
#define __OAUTH_UTIL_H__

#include "../../Common/StringUtil.h"

BOOL GetTimeStamp(wstring& timeStamp);
BOOL CreateSignatureHMACSHA1(wstring src, wstring secretKey, wstring& signature);

//UnicodeをUTF8に変換してURLエンコードする
BOOL UrlEncodeUTF8(LPCWSTR src, DWORD srcSize, wstring& dest);
//UnicodeをUTF8に変換してURLエンコードする
BOOL UrlEncodeUTF8(LPCWSTR src, DWORD srcSize, string& dest);
//URLデコードを行ってUTF8をUnicodeに変換する
BOOL UrlDecodeUTF8(LPCSTR src, DWORD srcSize, wstring& dest);
//URLデコードを行ってUTF8をUnicodeに変換する
BOOL UrlDecodeUTF8(LPCWSTR src, DWORD srcSize, wstring& dest);

#endif
