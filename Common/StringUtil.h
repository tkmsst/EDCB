#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include "Util.h"

void Format(string& strBuff, const char *format, ...);

void Format(wstring& strBuff, const WCHAR *format, ...);

void Replace(string& strBuff, const string strOld, const string strNew);

void Replace(wstring& strBuff, const wstring strOld, const wstring strNew);

void WtoA(wstring strIn, string& strOut);

void WtoUTF8(wstring strIn, string& strOut);

void AtoW(string strIn, wstring& strOut);

void UTF8toW(string strIn, wstring& strOut);

BOOL Separate(string strIn, string strSep, string& strLeft, string& strRight);

BOOL Separate(wstring strIn, wstring strSep, wstring& strLeft, wstring& strRight);

void ChkFolderPath(string& strPath);

void ChkFolderPath(wstring& strPath);

void ChkFileName(string& strPath);

void ChkFileName(wstring& strPath);

int CompareNoCase(string str1, string str2);

int CompareNoCase(wstring str1, wstring str2);

BOOL UrlDecode(LPCSTR src, DWORD srcSize, string& dest);

BOOL UrlDecode(LPCWSTR src, DWORD srcSize, wstring& dest);

void Trim(string& strBuff);

void Trim(wstring& strBuff);

string Tolower(string src);

wstring Tolower(wstring src);

void EscapeXmlString(wstring& src);

#endif
