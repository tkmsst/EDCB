#ifndef __UPNP_STRUCT_DEF_H__
#define __UPNP_STRUCT_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>
#include "SortListUtil.h"

#ifndef _WIN32
#define __int64 long long //64bit型
#endif

//生成、開放時は専用APIをできるだけ使うこと
//M-Searchのリクエスト情報
typedef struct _UPNP_MSEARCH_REQUEST_INFO{
	char* res;			//リクエストの生データ

	char* host;			//HOST:
	char* man;			//MAN:
	char* mx;			//MX:
	char* st;			//ST:
	char* userAgent;	//USER-AGENT:
}UPNP_MSEARCH_REQUEST_INFO;

UPNP_MSEARCH_REQUEST_INFO* UPNP_MSEARCH_REQUEST_INFO_New();
void UPNP_MSEARCH_REQUEST_INFO_Delete(void* item);
UPNP_MSEARCH_REQUEST_INFO* UPNP_MSEARCH_REQUEST_INFO_Clone(UPNP_MSEARCH_REQUEST_INFO* src);

//M-Searchのレスポンス情報（されたとき）
typedef struct _UPNP_MSEARCH_RES_DEV_INFO{
	char* uuid;

	int max_age;		//CACHE-CONTROL: max-age =
	int port;			//LOCATIONのポート番号
	char* uri;			//LOCATION: (DDDを取得するURL)(http://xxx.xxx.xxx.xxx:xxxxは省いたもの(/****/***.xml) 最低でも「/」は入れること)
	char* server;		//SERVER:
	char* usn;			//USN:
}UPNP_MSEARCH_RES_DEV_INFO;

UPNP_MSEARCH_RES_DEV_INFO* UPNP_MSEARCH_RES_DEV_INFO_New();
void UPNP_MSEARCH_RES_DEV_INFO_Delete(void* item);
UPNP_MSEARCH_RES_DEV_INFO* UPNP_MSEARCH_RES_DEV_INFO_Clone(UPNP_MSEARCH_RES_DEV_INFO* src);

//M-Searchのレスポンス情報（したとき）
typedef struct _UPNP_MSEARCH_RESPONSE_INFO{
	char* uuid;			//uuid
	char* res;			//レスポンスの生データ

	int max_age;		//CACHE-CONTROL: max-age =
	char* date;			//DATE:
	char* location;		//LOCATION: (DDDを取得するURL)
	char* server;		//SERVER:
	char* st;			//ST:
	char* usn;			//USN:
}UPNP_MSEARCH_RESPONSE_INFO;

UPNP_MSEARCH_RESPONSE_INFO* UPNP_MSEARCH_RESPONSE_INFO_New();
void UPNP_MSEARCH_RESPONSE_INFO_Delete(void* item);
UPNP_MSEARCH_RESPONSE_INFO* UPNP_MSEARCH_RESPONSE_INFO_Clone(UPNP_MSEARCH_RESPONSE_INFO* src);

//SSDPのNotify情報
typedef struct _UPNP_SSDP_NOTIFY_INFO{
	char* res;			//Notifyの生データ

	char* host;			//HOST:
	int max_age;		//CACHE-CONTROL: max-age =
	char* location;		//LOCATION: (DDDを取得するURL)
	char* nt;			//NT:
	char* nts;			//NTS:
	char* server;		//SERVER:
	char* usn;			//USN:
}UPNP_SSDP_NOTIFY_INFO;

UPNP_SSDP_NOTIFY_INFO* UPNP_SSDP_NOTIFY_INFO_New();
void UPNP_SSDP_NOTIFY_INFO_Delete(void* item);
UPNP_SSDP_NOTIFY_INFO* UPNP_SSDP_NOTIFY_INFO_Clone(UPNP_SSDP_NOTIFY_INFO* src);



#ifdef __cplusplus
}
#endif

#endif
