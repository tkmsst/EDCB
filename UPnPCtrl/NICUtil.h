#ifndef __MULTI_PLATFORM_NIC_UTIL_H__
#define __MULTI_PLATFORM_NIC_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "SortListUtil.h"

typedef struct _MP_NIC_INFO{
	char* name;			//インターフェース名
	char* ipv4;			//IPアドレス(v4)
//	char* ipv6;			//IPアドレス(v6)
	char* macAddress;	//MACアドレス("-"区切りの文字列)
	unsigned char macAddressValue[6];//MACアドレス("-"がない値)
}MP_NIC_INFO;

MP_NIC_INFO* MP_NIC_INFO_New();
void MP_NIC_INFO_Delete(void* item);
MP_NIC_INFO* MP_NIC_INFO_Clone(MP_NIC_INFO* src);

//NICの一覧情報を取得する
//戻り値：エラーでNULL、成功時検索結果のリスト、キー：char* のname、要素：MP_NIC_INFO*　不必要になったら上位層で開放すること
SORT_LIST_HANDLE MP_NIC_GetNICInfo(void);

#ifdef __cplusplus
}
#endif

#endif
