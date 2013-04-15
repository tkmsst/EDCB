#include "stdafx.h"

#include "MPInclude.h"

#include "HttpUtil.h"
#include "CharUtil.h"


HTTP_HEADER_FIELD_INFO* HTTP_HEADER_FIELD_INFO_New()
{
	HTTP_HEADER_FIELD_INFO* item = NULL;

	item = (HTTP_HEADER_FIELD_INFO*)malloc(sizeof(HTTP_HEADER_FIELD_INFO));
	if( item != NULL ){
		item->name = NULL;
		item->value = NULL;
	}
	return item;
}

void HTTP_HEADER_FIELD_INFO_Delete(void* item)
{
	HTTP_HEADER_FIELD_INFO* info = (HTTP_HEADER_FIELD_INFO*)item;
	if( info == NULL ){
		return ;
	}

	if( info->name != NULL ){
		free(info->name);
	}
	if( info->value != NULL ){
		free(info->value);
	}
	free(item);
}

HTTP_REQUEST_HEADER* HTTP_REQUEST_HEADER_New()
{
	HTTP_REQUEST_HEADER* item = NULL;

	item = (HTTP_REQUEST_HEADER*)malloc(sizeof(HTTP_REQUEST_HEADER));
	if( item != NULL ){
		item->method = NULL;
		item->uri = NULL;
		item->version = NULL;
		item->headerList = SORT_LIST_CreateHandle(0, SORT_LIST_COMPDEF_stricmp, NULL, HTTP_HEADER_FIELD_INFO_Delete);
	}
	return item;
}

void HTTP_REQUEST_HEADER_Delete(void* item)
{
	HTTP_REQUEST_HEADER* info = (HTTP_REQUEST_HEADER*)item;
	if( info == NULL ){
		return ;
	}

	if( info->method != NULL ){
		free(info->method);
	}
	if( info->uri != NULL ){
		free(info->uri);
	}
	if( info->version != NULL ){
		free(info->version);
	}
	if( info->headerList != NULL ){
		SORT_LIST_CloseHandle(&info->headerList);
	}
	free(item);
}

int MP_HTTP_RequestHeaderParse(char* src, HTTP_REQUEST_HEADER* header)
{
	char* leftBuff = NULL;
	char* rightBuff = NULL;
	char* tempBuff = NULL;
	int srcLength = 0;
	HTTP_HEADER_FIELD_INFO* headerItem = NULL;

	if( src == NULL || header == NULL ){
		return -1;
	}

	srcLength = (int)strlen(src);
	leftBuff = (char*)malloc(srcLength+1);
	rightBuff = (char*)malloc(srcLength+1);
	tempBuff = (char*)malloc(srcLength+1);

	if( leftBuff == NULL || rightBuff == NULL || tempBuff == NULL ){
		return -1;
	}

#ifdef _WIN32
	strcpy_s(rightBuff, srcLength+1, src);
#else
	strcpy(rightBuff, src);
#endif

	//Request-Line
	MP_STR_Separate(rightBuff, "\r\n", leftBuff, srcLength+1, rightBuff, srcLength+1);

	MP_STR_Separate(leftBuff, " ", tempBuff, srcLength+1, leftBuff, srcLength+1);
	header->method = (char*)malloc(strlen(tempBuff)+1);
#ifdef _WIN32
	strcpy_s(header->method, strlen(tempBuff)+1, tempBuff);
#else
	strcpy(header->method, tempBuff);
#endif

	MP_STR_Separate(leftBuff, " ", tempBuff, srcLength+1, leftBuff, srcLength+1);
	header->uri = (char*)malloc(strlen(tempBuff)+1);
#ifdef _WIN32
	strcpy_s(header->uri, strlen(tempBuff)+1, tempBuff);
#else
	strcpy(header->uri, tempBuff);
#endif

	header->version = (char*)malloc(strlen(leftBuff)+1);
#ifdef _WIN32
	strcpy_s(header->version, strlen(leftBuff)+1, leftBuff);
#else
	strcpy(header->version, leftBuff);
#endif

	//Header
	while(strlen(rightBuff) > 0 ){
		MP_STR_Separate(rightBuff, "\r\n", leftBuff, srcLength+1, rightBuff, srcLength+1);

		if( strlen(leftBuff) > 0 ){
			headerItem = HTTP_HEADER_FIELD_INFO_New();

			MP_STR_Separate(leftBuff, ":", tempBuff, srcLength+1, leftBuff, srcLength+1);

			MP_STR_Trim(tempBuff);
			MP_STR_Trim(leftBuff);

			headerItem->name = (char*)malloc(strlen(tempBuff)+1);
#ifdef _WIN32
			strcpy_s(headerItem->name, strlen(tempBuff)+1, tempBuff);
#else
			strcpy(headerItem->name, tempBuff);
#endif
			headerItem->value = (char*)malloc(strlen(leftBuff)+1);
#ifdef _WIN32
			strcpy_s(headerItem->value, strlen(leftBuff)+1, leftBuff);
#else
			strcpy(headerItem->value, leftBuff);
#endif

			SORT_LIST_AddItem(header->headerList, headerItem->name, headerItem);
		}
	}


	free(leftBuff);
	free(rightBuff);
	free(tempBuff);

	return 0;
}
