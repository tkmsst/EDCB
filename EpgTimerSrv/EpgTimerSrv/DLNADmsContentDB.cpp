#include "StdAfx.h"
#include "DLNADmsContentDB.h"

#include "../../Common/StringUtil.h"

CDLNADmsContentDB::CDLNADmsContentDB(void)
{
	this->root = new DLNA_DMS_CONTAINER_ITEM;
	this->root->objectID = L"0";
	this->root->info = NULL;

	this->nextObjectID = 1;
}


CDLNADmsContentDB::~CDLNADmsContentDB(void)
{
	map<wstring, DLNA_DMS_CONTENT_ITEM*>::iterator itr1;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr2;

	for( itr1 = contentList.begin(); itr1 != contentList.end(); itr1++){
		SAFE_DELETE(itr1->second);
	}
	for( itr2 = containerList.begin(); itr2 != containerList.end(); itr2++){
		SAFE_DELETE(itr2->second);
	}

	SAFE_DELETE(this->root);
}

void CDLNADmsContentDB::SetRootUri(wstring uri)
{
	if( lock.Lock(L"CDLNADmsContentDB::SetRootUri") == FALSE ){
		return;
	}

	this->rootUri = uri;

	lock.UnLock();
}

int CDLNADmsContentDB::CreateContainer(wstring parentObjectID, DLNA_DMS_CONTAINER_META_INFO* info, wstring& objectID)
{
	if( lock.Lock(L"CDLNADmsContentDB::CreateContainer") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTENT_ITEM*>::iterator itr1;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr2;
	wstring id = L"";
	DLNA_DMS_CONTAINER_ITEM* containerInfo = NULL;

	do{
		Format(id, L"%I64d", this->nextObjectID);

		itr1 = contentList.find(id);
		itr2 = containerList.find(id);

		this->nextObjectID++;
	}while(itr1 != contentList.end() || itr2 != containerList.end());

	containerInfo = new DLNA_DMS_CONTAINER_ITEM;
	containerInfo->objectID = id;
	containerInfo->parentObjectID = parentObjectID;
	containerInfo->info = new DLNA_DMS_CONTAINER_META_INFO;
	*containerInfo->info = *info;

	if( CompareNoCase(parentObjectID, L"0") == 0 ){
		containerList.insert(pair<wstring, DLNA_DMS_CONTAINER_ITEM*>(containerInfo->objectID, containerInfo));
		root->childContainer.insert(pair<wstring, DLNA_DMS_CONTAINER_ITEM*>(containerInfo->objectID, containerInfo));
	}else{
		itr2 = containerList.find(parentObjectID);
		if( itr2 == containerList.end() ){
			SAFE_DELETE(containerInfo);
			ret = ERR_FALSE;
			goto Err_End;
		}
		itr2->second->childContainer.insert(pair<wstring, DLNA_DMS_CONTAINER_ITEM*>(containerInfo->objectID, containerInfo));
		containerList.insert(pair<wstring, DLNA_DMS_CONTAINER_ITEM*>(containerInfo->objectID, containerInfo));
	}
	objectID = id;

Err_End:
	lock.UnLock();

	return ret;
}

int CDLNADmsContentDB::DeleteContainer(wstring objectID)
{
	if( lock.Lock(L"CDLNADmsContentDB::DeleteContainer") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr1;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr2;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr3;

	if( CompareNoCase(objectID, L"0") == 0 ){
		ret = ERR_FALSE;
		goto Err_End;
	}

	itr1 = containerList.find(objectID);
	if( itr1 == containerList.end() ){
		ret = ERR_FALSE;
		goto Err_End;
	}

	itr2 = containerList.find(itr1->second->parentObjectID);
	if( itr2 == containerList.end() ){
		ret = ERR_FALSE;
		goto Err_End;
	}

	itr3 = itr2->second->childContainer.find(objectID);
	if( itr3 == itr2->second->childContainer.end() ){
		ret = ERR_FALSE;
		goto Err_End;
	}
	itr2->second->childContainer.erase(itr3);

	SAFE_DELETE(itr1->second);
	containerList.erase(itr1);

Err_End:
	lock.UnLock();

	return ret;
}

int CDLNADmsContentDB::AddContent(wstring containerObjectID, DLNA_DMS_CONTENT_META_INFO* info, wstring& objectID)
{
	if( lock.Lock(L"CDLNADmsContentDB::AddContent") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTENT_ITEM*>::iterator itr1;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr2;
	wstring id = L"";
	DLNA_DMS_CONTENT_ITEM* contentInfo = NULL;

	do{
		Format(id, L"%I64d", this->nextObjectID);

		itr1 = contentList.find(id);
		itr2 = containerList.find(id);

		this->nextObjectID++;
	}while(itr1 != contentList.end() || itr2 != containerList.end());

	contentInfo = new DLNA_DMS_CONTENT_ITEM;
	contentInfo->objectID = id;
	contentInfo->parentObjectID = containerObjectID;
	contentInfo->info = new DLNA_DMS_CONTENT_META_INFO;
	*contentInfo->info = *info;

	if( CompareNoCase(objectID, L"0") == 0 ){
		contentList.insert(pair<wstring, DLNA_DMS_CONTENT_ITEM*>(contentInfo->objectID, contentInfo));
		root->childContent.insert(pair<wstring, DLNA_DMS_CONTENT_ITEM*>(contentInfo->objectID, contentInfo));
	}else{
		itr2 = containerList.find(containerObjectID);
		if( itr2 == containerList.end() ){
			SAFE_DELETE(contentInfo);
			ret = ERR_FALSE;
			goto Err_End;
		}
		itr2->second->childContent.insert(pair<wstring, DLNA_DMS_CONTENT_ITEM*>(contentInfo->objectID, contentInfo));
		contentList.insert(pair<wstring, DLNA_DMS_CONTENT_ITEM*>(contentInfo->objectID, contentInfo));
	}
	objectID = id;

Err_End:
	lock.UnLock();

	return ret;
}

int CDLNADmsContentDB::RemoveContent(wstring objectID)
{
	if( lock.Lock(L"CDLNADmsContentDB::RemoveContent") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTENT_ITEM*>::iterator itr1;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr2;
	map<wstring, DLNA_DMS_CONTENT_ITEM*>::iterator itr3;

	if( CompareNoCase(objectID, L"0") == 0 ){
		ret = ERR_FALSE;
		goto Err_End;
	}

	itr1 = contentList.find(objectID);
	if( itr1 == contentList.end() ){
		ret = ERR_FALSE;
		goto Err_End;
	}

	itr2 = containerList.find(itr1->second->parentObjectID);
	if( itr2 == containerList.end() ){
		ret = ERR_FALSE;
		goto Err_End;
	}

	itr3 = itr2->second->childContent.find(objectID);
	if( itr3 == itr2->second->childContent.end() ){
		ret = ERR_FALSE;
		goto Err_End;
	}
	itr2->second->childContent.erase(itr3);

	SAFE_DELETE(itr1->second);
	contentList.erase(itr1);

Err_End:
	lock.UnLock();

	return ret;
}

int CDLNADmsContentDB::GetChildItem(wstring containerObjectID, vector<DLNA_DMS_CONTAINER_INFO>* childContainerList, vector<DLNA_DMS_CONTENT_INFO>* childContentList)
{
	if( lock.Lock(L"CDLNADmsContentDB::GetChildItem") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr1;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr2;
	map<wstring, DLNA_DMS_CONTENT_ITEM*>::iterator itr3;

	map<wstring, DLNA_DMS_CONTAINER_ITEM*> sortContainer;
	map<wstring, DLNA_DMS_CONTENT_ITEM*> sortContetn;


	DLNA_DMS_CONTAINER_ITEM* parent = NULL;

	if( CompareNoCase(containerObjectID, L"0") == 0 ){
		parent = root;
	}else{
		itr1 = containerList.find(containerObjectID);
		if( itr1 == containerList.end() ){
			ret = ERR_FALSE;
			goto Err_End;
		}
		parent = itr1->second;
	}

	for( itr2 = parent->childContainer.begin(); itr2 != parent->childContainer.end(); itr2++ ){
		sortContainer.insert(pair<wstring, DLNA_DMS_CONTAINER_ITEM*>(itr2->second->info->title, itr2->second));
	}
	for( itr2 = sortContainer.begin(); itr2 != sortContainer.end(); itr2++ ){
		DLNA_DMS_CONTAINER_INFO item;
		item.objectID = itr2->second->objectID;
		item.parentObjectID = itr2->second->parentObjectID;
		item.uri = rootUri;
		item.info = *(itr2->second->info);

		childContainerList->push_back(item);
	}

	for( itr3 = parent->childContent.begin(); itr3 != parent->childContent.end(); itr3++ ){
		sortContetn.insert(pair<wstring, DLNA_DMS_CONTENT_ITEM*>(itr3->second->info->title, itr3->second));
	}
	for( itr3 = sortContetn.begin(); itr3 != sortContetn.end(); itr3++ ){
		wstring uri = L"";
		Format(uri, L"%s/%s", rootUri.c_str(), itr3->second->objectID.c_str());
		DLNA_DMS_CONTENT_INFO item;
		item.objectID = itr3->second->objectID;
		item.parentObjectID = itr3->second->parentObjectID;
		item.uri = uri;
		item.info = *(itr3->second->info);

		childContentList->push_back(item);
	}

Err_End:
	lock.UnLock();

	return ret;
}

int CDLNADmsContentDB::GetContainerItem(wstring containerObjectID, DLNA_DMS_CONTAINER_INFO* info)
{
	if( lock.Lock(L"CDLNADmsContentDB::GetContainerItem") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr1;

	DLNA_DMS_CONTAINER_ITEM* item = NULL;

	if( CompareNoCase(containerObjectID, L"0") == 0 ){
		item = root;
	}else{
		itr1 = containerList.find(containerObjectID);
		if( itr1 == containerList.end() ){
			ret = ERR_FALSE;
			goto Err_End;
		}
		item = itr1->second;
	}

	info->objectID = item->objectID;
	info->parentObjectID = item->parentObjectID;
	info->uri = rootUri;
	if( item->info != NULL ){
		info->info = *(item->info);
	}

Err_End:
	lock.UnLock();

	return ret;
}

int CDLNADmsContentDB::GetContentItem(wstring contentObjectID, DLNA_DMS_CONTENT_INFO* info)
{
	if( lock.Lock(L"CDLNADmsContentDB::GetContainerItem") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTENT_ITEM*>::iterator itr1;


	itr1 = contentList.find(contentObjectID);
	if( itr1 == contentList.end() ){
		ret = ERR_FALSE;
		goto Err_End;
	}

	info->objectID = itr1->second->objectID;
	info->parentObjectID = itr1->second->parentObjectID;
	info->uri = rootUri;
	if( itr1->second->info != NULL ){
		info->info = *(itr1->second->info);
	}

Err_End:
	lock.UnLock();

	return ret;
}

int CDLNADmsContentDB::SearchFilePath(string uri, wstring& filePath)
{
	if( lock.Lock(L"CDLNADmsContentDB::SearchFilePath") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTENT_ITEM*>::iterator itr1;
	wstring fileUri;
	wstring objectID;
	wstring buff1;
	wstring buff2;
	wstring tempBuff;

	AtoW(uri, fileUri);
	buff1 = this->rootUri;
	buff1 += L"/";

	//Separate(fileUri, L"?", fileUri, tempBuff);
	Separate(fileUri, buff1, buff2, objectID);

	itr1 = contentList.find(objectID);
	if( itr1 == contentList.end() ){
		ret = ERR_FALSE;
		goto Err_End;
	}

	filePath = itr1->second->info->filePath;

Err_End:
	lock.UnLock();

	return ret;
}

int CDLNADmsContentDB::SearchContainer(wstring virtualPath, wstring& objectID)
{
	if( lock.Lock(L"CDLNADmsContentDB::SearchContainer") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr1;
	DLNA_DMS_CONTAINER_ITEM* parentContainer = root;
	wstring findName;
	wstring buff1 = virtualPath;
	wstring buff2;

	BOOL find = FALSE;
	while( buff1.size() > 0 ){
		Separate(buff1, L"/", findName, buff1);
		if( findName.size() == 0 ){
			continue;
		}
		find = FALSE;
		for( itr1 = parentContainer->childContainer.begin(); itr1 != parentContainer->childContainer.end(); itr1++){
			if( CompareNoCase(itr1->second->info->title, findName ) == 0 ){
				find = TRUE;
				break;
			}
		}
		if( find == TRUE ){
			parentContainer = itr1->second;
			objectID = itr1->first;
		}else{
			ret = ERR_FALSE;
			break;
		}
	}

	if( find == FALSE ){
		objectID = L"";
		ret = ERR_FALSE;
	}

	lock.UnLock();

	return ret;
}

int CDLNADmsContentDB::CreateContainer2(wstring virtualPath, DLNA_DMS_CONTAINER_META_INFO* info, wstring& objectID)
{
	if( lock.Lock(L"CDLNADmsContentDB::CreateContainer2") == FALSE ){
		return ERR_FALSE;
	}

	int ret = NO_ERR;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itr1;
	DLNA_DMS_CONTAINER_ITEM* parentContainer = root;
	wstring findName;
	wstring buff1 = virtualPath;
	wstring buff2;
	wstring id = L"";
	DLNA_DMS_CONTAINER_ITEM* containerInfo = NULL;

	map<wstring, DLNA_DMS_CONTENT_ITEM*>::iterator itrID1;
	map<wstring, DLNA_DMS_CONTAINER_ITEM*>::iterator itrID2;

	BOOL find = FALSE;
	while( buff1.size() > 0 ){
		Separate(buff1, L"/", findName, buff1);
		if( findName.size() == 0 ){
			continue;
		}
		find = FALSE;
		for( itr1 = parentContainer->childContainer.begin(); itr1 != parentContainer->childContainer.end(); itr1++){
			if( CompareNoCase(itr1->second->info->title, findName ) == 0 ){
				find = TRUE;
				break;
			}
		}
		if( find == FALSE ){
			do{
				Format(id, L"%I64d", this->nextObjectID);

				itrID1 = contentList.find(id);
				itrID2 = containerList.find(id);

				this->nextObjectID++;
			}while(itrID1 != contentList.end() || itrID2 != containerList.end());

			containerInfo = new DLNA_DMS_CONTAINER_ITEM;
			containerInfo->parentObjectID = parentContainer->objectID;
			containerInfo->objectID = id;
			containerInfo->info = new DLNA_DMS_CONTAINER_META_INFO;
			if( buff1.size() == 0){
				*containerInfo->info = *info;
			}else{
				containerInfo->info->title = findName;
				containerInfo->info->uploadSupportFlag = 0;
				containerInfo->info->uploadFolderPath = L"";
			}

			parentContainer->childContainer.insert(pair<wstring, DLNA_DMS_CONTAINER_ITEM*>(containerInfo->objectID, containerInfo));
			containerList.insert(pair<wstring, DLNA_DMS_CONTAINER_ITEM*>(containerInfo->objectID, containerInfo));

			objectID = containerInfo->objectID;
		}else{
			objectID = itr1->first;
			parentContainer = itr1->second;
		}
	}

	lock.UnLock();

	return ret;
}
