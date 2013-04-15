#include "stdafx.h"

#include "SortListUtil.h"
#ifndef _WIN32
#define __int64 long long //64bit型
#endif
#define FIRST_LIST_RANGE 100

typedef struct _SORT_LIST_ITEM{
	void* key;
	void* item;
}SORT_LIST_ITEM;

typedef struct _SORT_LIST_HANDLE_ITEM{
	int multiKeyFlag;						//同一キーで追加できるかのフラグ（0:追加できない,1:追加できる）
	SORT_LIST_COMPARE compFunc;				//キー比較用の比較関数
	SORT_LIST_ITEM_DELETE deleteKeyFunc;	//解放時のキー解放関数
	SORT_LIST_ITEM_DELETE deleteItemFunc;	//解放時の要素解放関数

	void** itemList;					//リストのポインタ
	int itemListRange;					//リストのMAX保持数
	int itemCount;						//追加アイテムの個数
}SORT_LIST_HANDLE_ITEM;

//指定位置の前に追加する
int SORT_LIST_InsertBefore(
	SORT_LIST_HANDLE_ITEM* handle,		//[IN]handle
	int pos,							//[IN]挿入位置
	void* key,							//[IN]要素検索時のキーとなる物
	void* item							//[IN]追加する要素
)
{
	SORT_LIST_ITEM* addItem = NULL;
	if( handle == NULL ){
		return -1;
	}

	addItem = (SORT_LIST_ITEM*)malloc(sizeof(SORT_LIST_ITEM));
	if( addItem == NULL ){
		return -3;
	}
	addItem->key = key;
	addItem->item = item;

	if( handle->itemCount > pos ){
		//後ろに１つずらす
		memmove(&handle->itemList[pos+1], &handle->itemList[pos], sizeof(void*)*(handle->itemCount - pos) );
	}else{
		//指定値おかしいが最後に追加
		pos = handle->itemCount;
	}

	handle->itemList[pos] = addItem;
	handle->itemCount++;

	return 0;
}

//指定位置の後ろに追加する
int SORT_LIST_InsertAfter(
	SORT_LIST_HANDLE_ITEM* handle,		//[IN]handle
	int pos,							//[IN]挿入位置
	void* key,							//[IN]要素検索時のキーとなる物
	void* item							//[IN]追加する要素
)
{
	SORT_LIST_ITEM* addItem = NULL;
	if( handle == NULL ){
		return -1;
	}

	addItem = (SORT_LIST_ITEM*)malloc(sizeof(SORT_LIST_ITEM));
	if( addItem == NULL ){
		return -2;
	}
	addItem->key = key;
	addItem->item = item;

	if( handle->itemCount > pos+1 ){
		//後ろに１つずらす
		memmove(&handle->itemList[pos+2], &handle->itemList[pos+1], sizeof(void*)*(handle->itemCount - pos - 1) );
	}else{
		//指定値おかしいが最後に追加
		pos = handle->itemCount-1;
	}

	handle->itemList[pos+1] = addItem;
	handle->itemCount++;

	return 0;
}

//ハンドルの作成
//戻り値：ハンドル、エラー時NULL
SORT_LIST_HANDLE SORT_LIST_CreateHandle(
	int multiKeyFlag,						//[IN]同一キーで追加できるかのフラグ（0:追加できない,1:追加できる）
	SORT_LIST_COMPARE compFunc,				//[IN]キー比較用の比較関数
	SORT_LIST_ITEM_DELETE deleteKeyFunc,	//[IN]解放時のキー解放関数
	SORT_LIST_ITEM_DELETE deleteItemFunc	//[IN]解放時の要素解放関数
)
{
	SORT_LIST_HANDLE_ITEM* handle = NULL;
	if( compFunc == NULL ){
		return NULL;
	}

	handle = (SORT_LIST_HANDLE_ITEM*)malloc(sizeof(SORT_LIST_HANDLE_ITEM));
	if( handle != NULL ){
		handle->multiKeyFlag = multiKeyFlag;
		handle->compFunc = compFunc;
		handle->deleteKeyFunc = deleteKeyFunc;
		handle->deleteItemFunc = deleteItemFunc;
		handle->itemCount = 0;
		handle->itemListRange = FIRST_LIST_RANGE;
		handle->itemList = (void**)malloc(sizeof(void*)*handle->itemListRange);
		if( handle->itemList == NULL ){
			free(handle);
			handle = NULL;
		}
	}

	return handle;
}

//ハンドルの解放
//解放後handleはNULLに
void SORT_LIST_CloseHandle(
	SORT_LIST_HANDLE* handle			//[IN]SORT_LIST_CreateHandleの戻り値
)
{
	int i=0;
	SORT_LIST_HANDLE_ITEM* info = NULL;
	SORT_LIST_ITEM* item = NULL;

	if( handle == NULL ){
		return;
	}
	info = (SORT_LIST_HANDLE_ITEM*)*handle;
	if( info != NULL ){
		for( i=0; i<info->itemCount; i++ ){
			item = (SORT_LIST_ITEM*)info->itemList[i];
			if( info->deleteKeyFunc != NULL ){
				info->deleteKeyFunc(item->key);
			}
			if( info->deleteItemFunc != NULL ){
				info->deleteItemFunc(item->item);
			}
			free(item);
		}
		free(info->itemList);
		free(info);
		*handle = NULL;
	}
}

//要素の追加
//戻り値：0未満でエラー、0以上で成功
int SORT_LIST_AddItem(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	void* key,							//[IN]要素検索時のキーとなる物
	void* item							//[IN]追加する要素
)
{
	SORT_LIST_HANDLE_ITEM* info = NULL;
	void** reallocList = NULL;
	int lowPos = 0;
	int midPos = 0;
	int highPos = 0;
	int compRes1 = 0;
	int compRes2 = 0;
	SORT_LIST_ITEM* comp1 = NULL;
	SORT_LIST_ITEM* comp2 = NULL;
	SORT_LIST_ITEM* addItem = NULL;
	int addMode = -1;

	if( handle == NULL ){
		return -1;
	}
	info = (SORT_LIST_HANDLE_ITEM*)handle;

	if( info->compFunc == NULL ){
		return -2;
	}

	if( info->itemListRange < info->itemCount+1 ){
		//サイズ越えるので拡張
		reallocList = (void**)realloc(info->itemList, sizeof(void*)*(info->itemListRange+FIRST_LIST_RANGE));
		if( reallocList == NULL ){
			return -3;
		}
		info->itemList = reallocList;
		info->itemListRange += FIRST_LIST_RANGE;
	}

	if( info->itemCount == 0 ){
		addItem = (SORT_LIST_ITEM*)malloc(sizeof(SORT_LIST_ITEM));
		addItem->key = key;
		addItem->item = item;
		info->itemList[0] = addItem;
		info->itemCount++;
	}else{
		//挿入位置の検索
		lowPos = 0;
		highPos = info->itemCount-1;
		while( lowPos <= highPos ){
			midPos = (lowPos + highPos) / 2;
			comp1 = (SORT_LIST_ITEM*)info->itemList[midPos];
			compRes1 = info->compFunc(key, comp1->key);
			if( compRes1 == 0 ){
				if( info->multiKeyFlag == 0 ){
					//同一キーなのでエラー
					return -4;
				}else{
					//追加位置
					//後方に追加
					addMode=1;
					break;
				}
			}else if( compRes1 < 0 ){
				highPos =  midPos-1;
				if( lowPos > highPos ){
					//追加位置
					//前方に追加
					addMode=0;
					break;
				}
			}else{
				lowPos =  midPos+1;
				if( lowPos > highPos ){
					//追加位置
					//後方に追加
					addMode=1;
					break;
				}
			}
		}
		if( addMode==0 ){
			SORT_LIST_InsertBefore(info, midPos, key, item);
		}else if( addMode==1 ){
			SORT_LIST_InsertAfter(info, midPos, key, item);
		}else{
			return -5;
		}
	}

	return 0;
}

//要素の削除
//戻り値：0未満でエラー、0以上で成功
int SORT_LIST_DeleteItem(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	void* key							//[IN]要素検索時のキーとなる物
)
{
	SORT_LIST_HANDLE_ITEM* info = NULL;
	SORT_LIST_ITEM* delItem = NULL;
	int lowPos = 0;
	int midPos = 0;
	int highPos = 0;
	int compRes = 0;

	if( handle == NULL ){
		return -1;
	}
	info = (SORT_LIST_HANDLE_ITEM*)handle;

	if( info->compFunc == NULL ){
		return -2;
	}
	if( info->itemCount <= 0 ){
		return -3;
	}

	//削除アイテムの検索
	lowPos = 0;
	highPos = info->itemCount-1;
	while( lowPos <= highPos ){
		midPos = (lowPos + highPos) / 2;
		delItem = (SORT_LIST_ITEM*)info->itemList[midPos];
		compRes = info->compFunc(delItem->key, key);
		if( compRes == 0 ){
			//削除処理
			if( info->deleteKeyFunc != NULL ){
				info->deleteKeyFunc(delItem->key);
			}
			if( info->deleteItemFunc != NULL ){
				info->deleteItemFunc(delItem->item);
			}
			free(delItem);
			//前に１つずらす
			if( info->itemCount - midPos - 1 > 0 ){
				memmove(&info->itemList[midPos], &info->itemList[midPos+1], sizeof(void*)*(info->itemCount - midPos - 1) );
			}
			info->itemCount--;
			break;
		}else if(compRes < 0){
			lowPos =  midPos+1;
		}else{
			highPos =  midPos-1;
		}
	}
	return 0;
}


//指定Indexの要素の削除
//戻り値：0未満でエラー、0以上で成功
int SORT_LIST_DeleteItemByIndex(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	int index							//[IN]削除する要素Index
)
{
	SORT_LIST_HANDLE_ITEM* info = NULL;
	SORT_LIST_ITEM* delItem = NULL;

	if( handle == NULL ){
		return -1;
	}
	info = (SORT_LIST_HANDLE_ITEM*)handle;

	if( info->compFunc == NULL ){
		return -2;
	}
	if( info->itemCount <= 0 ){
		return -3;
	}

	//削除アイテム
	delItem = (SORT_LIST_ITEM*)info->itemList[index];
	//削除処理
	if( info->deleteKeyFunc != NULL ){
		info->deleteKeyFunc(delItem->key);
	}
	if( info->deleteItemFunc != NULL ){
		info->deleteItemFunc(delItem->item);
	}
	free(delItem);
	//前に１つずらす
	if( info->itemCount - index - 1 > 0 ){
		memmove(&info->itemList[index], &info->itemList[index+1], sizeof(void*)*(info->itemCount - index - 1) );
	}
	info->itemCount--;

	return 0;
}

//要素の数を取得する
//戻り値：0未満でエラー、0以上で要素数
int SORT_LIST_GetCount(
	SORT_LIST_HANDLE handle				//[IN]SORT_LIST_CreateHandleの戻り値
)
{
	SORT_LIST_HANDLE_ITEM* info = NULL;

	if( handle == NULL ){
		return -1;
	}
	info = (SORT_LIST_HANDLE_ITEM*)handle;

	return info->itemCount;
}

//指定Indexの要素の取得
//戻り値：要素、エラー時NULL
void* SORT_LIST_GetItemByIndex(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	int index							//[IN]取得する要素Index
)
{
	SORT_LIST_HANDLE_ITEM* info = NULL;
	SORT_LIST_ITEM* item = NULL;

	if( handle == NULL ){
		return NULL;
	}
	info = (SORT_LIST_HANDLE_ITEM*)handle;
	if( info->itemCount <= index ){
		return NULL;
	}
	item = (SORT_LIST_ITEM*)info->itemList[index];

	return item->item;
}

//指定Indexのキーの取得
//戻り値：キー、エラー時NULL
void* SORT_LIST_GetKeyByIndex(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	int index							//[IN]取得する要素Index
)
{
	SORT_LIST_HANDLE_ITEM* info = NULL;
	SORT_LIST_ITEM* item = NULL;

	if( handle == NULL ){
		return NULL;
	}
	info = (SORT_LIST_HANDLE_ITEM*)handle;
	if( info->itemCount <= index ){
		return NULL;
	}
	item = (SORT_LIST_ITEM*)info->itemList[index];

	return item->key;
}

//指定キーの要素の取得
//戻り値：要素、エラー時NULL
void* SORT_LIST_FindItem(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	void* key							//[IN]検索キー
)
{
	SORT_LIST_HANDLE_ITEM* info = NULL;
	SORT_LIST_ITEM* item = NULL;
	int lowPos = 0;
	int midPos = 0;
	int highPos = 0;
	int compRes = 0;
	int findFlag = 0;

	if( handle == NULL ){
		return NULL;
	}
	info = (SORT_LIST_HANDLE_ITEM*)handle;

	if( info->compFunc == NULL ){
		return NULL;
	}
	if( info->itemCount <= 0 ){
		return NULL;
	}

	//アイテムの検索
	lowPos = 0;
	highPos = info->itemCount-1;
	while( lowPos <= highPos ){
		midPos = (lowPos + highPos) / 2;
		item = (SORT_LIST_ITEM*)info->itemList[midPos];
		compRes = info->compFunc(item->key, key);
		if( compRes == 0 ){
			findFlag = 1;
			break;
		}else if(compRes < 0){
			lowPos =  midPos+1;
		}else{
			highPos =  midPos-1;
		}
		item = NULL;
	}
	if( findFlag == 0 ){
		return NULL;
	}
	return item->item;
}

//要素のクリア
void SORT_LIST_Clear(
	SORT_LIST_HANDLE handle				//[IN]SORT_LIST_CreateHandleの戻り値
)
{
	int i=0;
	SORT_LIST_HANDLE_ITEM* info = NULL;
	SORT_LIST_ITEM* item = NULL;

	if( handle == NULL ){
		return ;
	}
	info = (SORT_LIST_HANDLE_ITEM*)handle;

	if( info->itemCount <= 0 ){
		return ;
	}

	for( i=0; i<info->itemCount; i++ ){
		item = (SORT_LIST_ITEM*)info->itemList[i];
		if( info->deleteKeyFunc != NULL ){
			info->deleteKeyFunc(item->key);
		}
		if( info->deleteItemFunc != NULL ){
			info->deleteItemFunc(item->item);
		}
		free(item);
	}
	info->itemCount = 0;
}


//汎用比較用関数
//int用
int SORT_LIST_COMPDEF_int(void* item1, void* item2)
{
	int info1 = (int)item1;
	int info2 = (int)item2;
	if( info1 < info2 ){
		return -1;
	}else
	if( info1 == info2 ){
		return 0;
	}else{
		return 1;
	}
}

//__int64*（64bit型変数）用
int SORT_LIST_COMPDEF_int64p(void* item1, void* item2)
{
	__int64* info1 = (__int64*)item1;
	__int64* info2 = (__int64*)item2;
	if( *info1 < *info2 ){
		return -1;
	}else
	if( *info1 == *info2 ){
		return 0;
	}else{
		return 1;
	}
}

//char*用strcmp
int SORT_LIST_COMPDEF_strcmp(void* item1, void* item2)
{
	char* info1 = (char*)item1;
	char* info2 = (char*)item2;

	return strcmp(info1, info2);
}

//char*用stricmp
int SORT_LIST_COMPDEF_stricmp(void* item1, void* item2)
{
	char* info1 = (char*)item1;
	char* info2 = (char*)item2;

#ifdef _WIN32
	return _stricmp(info1, info2);
#else
	//Linux系
	return strcasecmp(info1, info2);
#endif
}

//汎用delete関数
//freeで比較
void SORT_LIST_DELDEF_free(void* item1)
{
	free(item1);
}
