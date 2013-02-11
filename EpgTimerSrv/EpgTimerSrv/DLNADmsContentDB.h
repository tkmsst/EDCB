#pragma once

#include "../../Common/CommonDef.h"
#include "../../Common/LockUtil.h"

typedef struct _DLNA_DMS_CONTAINER_META_INFO{
	wstring uploadFolderPath;
	char uploadSupportFlag;

	wstring title;
}DLNA_DMS_CONTAINER_META_INFO;

typedef struct _DLNA_DMS_CONTENT_META_INFO{
	wstring filePath;
	char deleteSupportFlag;

	wstring title;
	wstring upnpClass;
	wstring mimeType;
	wstring protocolInfo;
	int durationSec;
	wstring date;
	__int64 fileSize;
	_DLNA_DMS_CONTENT_META_INFO(void){
		filePath = L"";
		deleteSupportFlag = 0;
		title = L"";
		upnpClass = L"";
		mimeType = L"";
		protocolInfo = L"";
		durationSec = -1;
		date = L"";
		fileSize = -1;
	}
}DLNA_DMS_CONTENT_META_INFO;
/*
typedef struct _DLNA_DMS_CONTENT_TRANSFER_INFO{
	wstring filePath;
	wstring mimeType;
	wstring ORG_PN;
}DLNA_DMS_CONTENT_TRANSFER_INFO;
*/
typedef struct _DLNA_DMS_CONTENT_ITEM{
	wstring objectID;
	wstring parentObjectID;

	DLNA_DMS_CONTENT_META_INFO* info;
	//vector<DLNA_DMS_CONTENT_TRANSFER_INFO> transferItem;
	_DLNA_DMS_CONTENT_ITEM(void){
		info = NULL;
	}
	~_DLNA_DMS_CONTENT_ITEM(void){
		SAFE_DELETE(info);
	}
}DLNA_DMS_CONTENT_ITEM;

typedef struct _DLNA_DMS_CONTAINER_ITEM{
	wstring objectID;
	wstring parentObjectID;

	DLNA_DMS_CONTAINER_META_INFO* info;

	map<wstring, struct _DLNA_DMS_CONTAINER_ITEM*> childContainer;
	map<wstring, DLNA_DMS_CONTENT_ITEM*> childContent;

	_DLNA_DMS_CONTAINER_ITEM(void){
		info = NULL;
	}
	~_DLNA_DMS_CONTAINER_ITEM(void){
		SAFE_DELETE(info);
	}
}DLNA_DMS_CONTAINER_ITEM;



typedef struct _DLNA_DMS_CONTAINER_INFO{
	wstring objectID;
	wstring parentObjectID;
	wstring uri;

	DLNA_DMS_CONTAINER_META_INFO info;
}DLNA_DMS_CONTAINER_INFO;

typedef struct _DLNA_DMS_CONTENT_INFO{
	wstring objectID;
	wstring parentObjectID;
	wstring uri;

	DLNA_DMS_CONTENT_META_INFO info;
}DLNA_DMS_CONTENT_INFO;

class CDLNADmsContentDB
{
public:
	CDLNADmsContentDB(void);
	~CDLNADmsContentDB(void);

	void SetRootUri(wstring uri);

	int CreateContainer(wstring parentObjectID, DLNA_DMS_CONTAINER_META_INFO* info, wstring& objectID);
	int DeleteContainer(wstring objectID);
	int AddContent(wstring containerObjectID, DLNA_DMS_CONTENT_META_INFO* info, wstring& objectID);
	//int AddTransferContent(wstring contentObjectID, DLNA_DMS_CONTENT_TRANSFER_INFO* info);
	int RemoveContent(wstring objectID);

	int GetChildItem(wstring containerObjectID, vector<DLNA_DMS_CONTAINER_INFO>* childContainerList, vector<DLNA_DMS_CONTENT_INFO>* childContentList);
	int GetContainerItem(wstring containerObjectID, DLNA_DMS_CONTAINER_INFO* info);
	int GetContentItem(wstring contentObjectID, DLNA_DMS_CONTENT_INFO* info);

	int SearchFilePath(string uri, wstring& filePath);

	int SearchContainer(wstring virtualPath, wstring& objectID);
	int CreateContainer2(wstring virtualPath, DLNA_DMS_CONTAINER_META_INFO* info, wstring& objectID);
protected:
	CLockUtil lock;

	wstring rootUri;
	DLNA_DMS_CONTAINER_ITEM* root;
	unsigned __int64 nextObjectID;

	map<wstring, DLNA_DMS_CONTAINER_ITEM*> containerList;
	map<wstring, DLNA_DMS_CONTENT_ITEM*> contentList;

};

