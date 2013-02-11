#include "stdafx.h"
#include "OAuthUtil.h"

#include <wincrypt.h>
#pragma comment (lib, "Crypt32.lib")


#define I64_1SEC ((__int64)10000000)

BOOL GetTimeStamp(wstring& timeStamp)
{
	SYSTEMTIME utcTime;
	GetSystemTime(&utcTime);

	SYSTEMTIME startTime;
	startTime.wYear = 1970;
	startTime.wMonth = 1;
	startTime.wDay = 1;
	startTime.wHour = 0;
	startTime.wMinute = 0;
	startTime.wSecond = 0;
	startTime.wMilliseconds = 0;

	FILETIME utcFTime;
	SystemTimeToFileTime( &utcTime, &utcFTime );
	FILETIME startFTime;
	SystemTimeToFileTime( &startTime, &startFTime );

	__int64 utc64Time = ((__int64)utcFTime.dwHighDateTime)<<32 | utcFTime.dwLowDateTime;
	__int64 start64Time = ((__int64)startFTime.dwHighDateTime)<<32 | startFTime.dwLowDateTime;
	__int64 totalSec = (utc64Time-start64Time)/(I64_1SEC);

	Format(timeStamp, L"%I64d", totalSec);

	return TRUE;
}

BOOL CreateSignatureHMACSHA1(wstring src, wstring secretKey, wstring& signature)
{
	signature = L"";

	string hashSrc = "";
	string hashKey = "";
	WtoUTF8(src, hashSrc);
	WtoUTF8(secretKey, hashKey);

	HCRYPTPROV cryptProv = NULL;
	HCRYPTHASH cryptHash = NULL;
	BYTE key[65];
	DWORD keySize = 0;
	BYTE ipad[65];
	BYTE opad[65];
	ZeroMemory(key, 65);
	ZeroMemory(ipad, 65);
	ZeroMemory(opad, 65);

	BYTE* firstHash = NULL;
	DWORD firstHashSize = 0;
	BYTE* secondHash = NULL;
	DWORD secondHashSize = 0;

	WCHAR* base64 = NULL;
	DWORD base64Size = 0;

	if ( CryptAcquireContext(&cryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) == FALSE ){
		goto Err_End;
	}

	if( hashKey.size() > 64 ){
		if ( CryptCreateHash(cryptProv, CALG_SHA1, 0, 0, &cryptHash) == FALSE ){
			goto Err_End;
		}
		if( CryptHashData(cryptHash, (BYTE*)hashKey.c_str(), (DWORD)hashKey.length(), 0) == FALSE ){
			goto Err_End;
		}
		if( CryptGetHashParam(cryptHash, HP_HASHVAL, NULL, &keySize, 0 ) == FALSE ){
			goto Err_End;
		}
		if( CryptGetHashParam(cryptHash, HP_HASHVAL, key, &keySize, 0 ) == FALSE ){
			goto Err_End;
		}
		CryptDestroyHash(cryptHash);
		cryptHash = NULL;
	}else{
		keySize = (DWORD)hashKey.size();
		memcpy(key, hashKey.c_str(), keySize);
	}
	memcpy(ipad, key, keySize);
	memcpy(opad, key, keySize);
	for( int i=0; i<64; i++ ){
		ipad[i] ^= 0x36;
		opad[i] ^= 0x5c;
	}

	if ( CryptCreateHash(cryptProv, CALG_SHA1, 0, 0, &cryptHash) == FALSE ){
		goto Err_End;
	}
	if( CryptHashData(cryptHash, ipad, 64, 0) == FALSE ){
		goto Err_End;
	}
	if( CryptHashData(cryptHash, (BYTE*)hashSrc.c_str(), (DWORD)hashSrc.size(), 0) == FALSE ){
		goto Err_End;
	}
	if( CryptGetHashParam(cryptHash, HP_HASHVAL, NULL, &firstHashSize, 0 ) == FALSE ){
		goto Err_End;
	}
	firstHash = new BYTE[firstHashSize];
	if( CryptGetHashParam(cryptHash, HP_HASHVAL, firstHash, &firstHashSize, 0 ) == FALSE ){
		goto Err_End;
	}
	CryptDestroyHash(cryptHash);
	cryptHash = NULL;

	if ( CryptCreateHash(cryptProv, CALG_SHA1, 0, 0, &cryptHash) == FALSE ){
		goto Err_End;
	}
	if( CryptHashData(cryptHash, opad, 64, 0) == FALSE ){
		goto Err_End;
	}
	if( CryptHashData(cryptHash, firstHash, firstHashSize, 0) == FALSE ){
		goto Err_End;
	}
	if( CryptGetHashParam(cryptHash, HP_HASHVAL, NULL, &secondHashSize, 0 ) == FALSE ){
		goto Err_End;
	}
	secondHash = new BYTE[secondHashSize];
	if( CryptGetHashParam(cryptHash, HP_HASHVAL, secondHash, &secondHashSize, 0 ) == FALSE ){
		goto Err_End;
	}
	CryptDestroyHash(cryptHash);
	cryptHash = NULL;

	//Base64
	if( CryptBinaryToString( secondHash, secondHashSize, CRYPT_STRING_BASE64, NULL, &base64Size ) == FALSE){
		goto Err_End;
	}
   base64 = new WCHAR[ base64Size + 1 ];
   if( CryptBinaryToString( secondHash, secondHashSize, CRYPT_STRING_BASE64, base64, &base64Size ) == FALSE ){
		goto Err_End;
   }
   signature = base64;
   //最後に\r\n入ってしまうみたいなので除去
   Replace(signature, L"\r\n", L"");

Err_End:
	SAFE_DELETE_ARRAY(base64);
	SAFE_DELETE_ARRAY(secondHash);
	SAFE_DELETE_ARRAY(firstHash);

	if( cryptHash !=NULL ){
		CryptDestroyHash(cryptHash);
	}
	if( cryptProv != NULL ){
		CryptReleaseContext(cryptProv, 0);
	}

	if( signature.size() > 0 ){
		return TRUE;
	}else{
		return FALSE;
	}
}


BOOL UrlEncodeUTF8(LPCWSTR src, DWORD srcSize, wstring& dest)
{
	if( src == NULL || srcSize == 0 ){
		return FALSE;
	}

	char* pBuff = NULL;
	int iLen = 0;

	iLen = WideCharToMultiByte(CP_UTF8, 0, src, -1, NULL, 0, NULL, NULL);
	pBuff = new char[iLen+1];
	ZeroMemory(pBuff, iLen+1);
	WideCharToMultiByte(CP_UTF8, 0, src, -1, pBuff, iLen, NULL, NULL);

	string destBuff;

	for( int i=0; i<iLen; i++ ){
		if( ( pBuff[i] >= 'A' && pBuff[i] <= 'Z' ) ||
			( pBuff[i] >= 'a' && pBuff[i] <= 'z' ) ||
			( pBuff[i] >= '0' && pBuff[i] <= '9' ) ||
			pBuff[i] == '.' ||
			pBuff[i] == '-' ||
			pBuff[i] == '_' ||
			pBuff[i] == '~' 
			)
		{
			destBuff+=pBuff[i];
		}else if( pBuff[i] == ' ' ){
			destBuff+="%20";
		}else if( pBuff[i] == '\0' ){
		}else{
			char cEnc[4]="";
			sprintf_s( cEnc, 4, "%%%02X", (BYTE)pBuff[i] );
			destBuff+=cEnc;
		}
	}

	delete[] pBuff;

	AtoW(destBuff, dest);

	return TRUE;
}

BOOL UrlEncodeUTF8(LPCWSTR src, DWORD srcSize, string& dest)
{
	if( src == NULL || srcSize == 0 ){
		return FALSE;
	}

	char* pBuff = NULL;
	int iLen = 0;

	iLen = WideCharToMultiByte(CP_UTF8, 0, src, -1, NULL, 0, NULL, NULL);
	pBuff = new char[iLen+1];
	ZeroMemory(pBuff, iLen+1);
	WideCharToMultiByte(CP_UTF8, 0, src, -1, pBuff, iLen, NULL, NULL);

	for( int i=0; i<iLen; i++ ){
		if( ( pBuff[i] >= 'A' && pBuff[i] <= 'Z' ) ||
			( pBuff[i] >= 'a' && pBuff[i] <= 'z' ) ||
			( pBuff[i] >= '0' && pBuff[i] <= '9' ) ||
			pBuff[i] == '.' ||
			pBuff[i] == '-' ||
			pBuff[i] == '_' ||
			pBuff[i] == '~' 
			)
		{
			dest+=pBuff[i];
		}else if( pBuff[i] == ' ' ){
			dest+="%20";
		}else if( pBuff[i] == '\0' ){
		}else{
			char cEnc[4]="";
			sprintf_s( cEnc, 4, "%%%02X", (BYTE)pBuff[i] );
			dest+=cEnc;
		}
	}

	delete[] pBuff;

	return TRUE;
}

//URLデコードを行ってUTF8をUnicodeに変換する
BOOL UrlDecodeUTF8(LPCSTR src, DWORD srcSize, wstring& dest)
{
	if( src == NULL ){
		return FALSE;
	}

	string utf8;
	for( DWORD i=0; i<srcSize; i++ ){
		if( src[i] == '%' ){
			if( i+2 > srcSize ){
				break;
			}
			char tmp[3]="";
			tmp[0] = src[i+1];
			tmp[1] = src[i+2];
			CHAR *endstr;
			char tmp2[2]="";
			tmp2[0] = (CHAR)strtol(tmp, &endstr, 16);
			utf8 += tmp2;
		}else if( src[i] == '+' ){
			utf8 += " ";
		}else if( src[i] == '\0' ){
			break;
		}else{
			char tmp[2]="";
			tmp[0] = src[i];
			utf8 += tmp;
		}
	}

	int iLen = MultiByteToWideChar( CP_UTF8, 0, utf8.c_str(), -1, NULL, 0 );
	WCHAR* pwszBuff = new WCHAR[iLen+1];
	ZeroMemory(pwszBuff, sizeof(WCHAR)*(iLen+1));
	MultiByteToWideChar( CP_UTF8, 0, utf8.c_str(), -1, pwszBuff, iLen );

	dest = pwszBuff;
	
	delete[] pwszBuff;

	return TRUE;
}

BOOL UrlDecodeUTF8(LPCWSTR src, DWORD srcSize, wstring& dest)
{
	if( src == NULL ){
		return FALSE;
	}

	string utf8;
	for( DWORD i=0; i<srcSize; i++ ){
		if( src[i] == '%' ){
			if( i+2 > srcSize ){
				break;
			}
			WCHAR tmp[3]=L"";
			tmp[0] = (char)src[i+1];
			tmp[1] = (char)src[i+2];

			WCHAR *endstr;
			char tmp2[2]="";
			tmp2[0] = (char)wcstol(tmp, &endstr, 16);
			utf8 += tmp2;

			i+=2;
		}else if( src[i] == '+' ){
			utf8 += " ";
		}else if( src[i] == '\0' ){
			break;
		}else{
			char tmp[2]="";
			tmp[0] = (char)src[i];
			utf8 += tmp;
		}
	}

	int iLen = MultiByteToWideChar( CP_UTF8, 0, utf8.c_str(), -1, NULL, 0 );
	WCHAR* pwszBuff = new WCHAR[iLen+1];
	ZeroMemory(pwszBuff, sizeof(WCHAR)*(iLen+1));
	MultiByteToWideChar( CP_UTF8, 0, utf8.c_str(), -1, pwszBuff, iLen );

	dest = pwszBuff;
	
	delete[] pwszBuff;

	return TRUE;
}
