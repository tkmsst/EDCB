#ifndef __MULTI_PLATFORM_HTTP_UTIL_H__
#define __MULTI_PLATFORM_HTTP_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "SortListUtil.h"

typedef struct _HTTP_HEADER_FIELD_INFO{
	char* name;
	char* value;
}HTTP_HEADER_FIELD_INFO;
HTTP_HEADER_FIELD_INFO* HTTP_HEADER_FIELD_INFO_New();
void HTTP_HEADER_FIELD_INFO_Delete(void* item);

typedef struct _HTTP_REQUEST_HEADER{
	char* method;
	char* uri;
	char* version;
	SORT_LIST_HANDLE headerList; //キ－：HTTP_HEADER_FIELD_INFOのname, 値：HTTP_HEADER_FIELD_INFOのポインタ
}HTTP_REQUEST_HEADER;
HTTP_REQUEST_HEADER* HTTP_REQUEST_HEADER_New();
void HTTP_REQUEST_HEADER_Delete(void* item);

int MP_HTTP_RequestHeaderParse(char* src, HTTP_REQUEST_HEADER* header);


#ifdef __cplusplus
}
#endif

#endif
