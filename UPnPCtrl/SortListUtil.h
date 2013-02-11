#ifndef __SORT_LIST_UTIL_H__
#define __SORT_LIST_UTIL_H__

/*
使い方

キーによる検索が可能なリストを作成して操作するもの
（追加時にソートしながら追加）

比較用関数の登録は必須
要素開放用はなくても可（その場合は上位層で開放すること）
スレッドセーフではないので、追加、削除と参照が同時に発生しそうであれば上位層で排他制御をすること

SORT_LIST_CreateHandle()
で作成
↓
SORT_LIST_AddItem()
で要素を順次追加
キーと要素が構造体や文字列の場合は動的に確保し、上位層で勝手に開放されないようにすること
↓
SORT_LIST_FindItem()やSORT_LIST_GetItemByIndex()
で要素へのアクセスをする
↓
SORT_LIST_CloseHandle()
必要なくなれば解放

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef void* SORT_LIST_HANDLE;

//要素比較用の関数
//戻り値 負の数:item1<item2,0:item1==item2,正の数:item1>item2
typedef int (*SORT_LIST_COMPARE)(
	void* item1,
	void* item2
);

//解放時の要素解放関数
typedef void (*SORT_LIST_ITEM_DELETE)(
	void* item1
);

//ハンドルの作成
//戻り値：ハンドル、エラー時NULL
SORT_LIST_HANDLE SORT_LIST_CreateHandle(
	int multiKeyFlag,						//[IN]同一キーで追加できるかのフラグ（0:追加できない,1:追加できる）
	SORT_LIST_COMPARE compFunc,				//[IN]キー比較用の比較関数
	SORT_LIST_ITEM_DELETE deleteKeyFunc,	//[IN]解放時のキー解放関数
	SORT_LIST_ITEM_DELETE deleteItemFunc	//[IN]解放時の要素解放関数
);

//ハンドルの解放
//解放後handleはNULLに
void SORT_LIST_CloseHandle(
	SORT_LIST_HANDLE* handle			//[IN]SORT_LIST_CreateHandleの戻り値
);

//要素の追加
//戻り値：0未満でエラー、0以上で成功
int SORT_LIST_AddItem(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	void* key,							//[IN]要素検索時のキーとなる物
	void* item							//[IN]追加する要素
);

//要素の削除
//戻り値：0未満でエラー、0以上で成功
int SORT_LIST_DeleteItem(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	void* key							//[IN]要素検索時のキーとなる物
);

//指定Indexの要素の削除
//戻り値：0未満でエラー、0以上で成功
int SORT_LIST_DeleteItemByIndex(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	int index							//[IN]削除する要素Index
);

//要素の数を取得する
//戻り値：0未満でエラー、0以上で要素数
int SORT_LIST_GetCount(
	SORT_LIST_HANDLE handle				//[IN]SORT_LIST_CreateHandleの戻り値
);

//指定Indexの要素の取得
//戻り値：要素、エラー時NULL
void* SORT_LIST_GetItemByIndex(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	int index							//[IN]取得する要素Index
);

//指定Indexのキーの取得
//戻り値：キー、エラー時NULL
void* SORT_LIST_GetKeyByIndex(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	int index							//[IN]取得するキーIndex
);

//指定キーの要素の取得
//戻り値：要素、エラー時NULL
void* SORT_LIST_FindItem(
	SORT_LIST_HANDLE handle,			//[IN]SORT_LIST_CreateHandleの戻り値
	void* key							//[IN]検索キー
);

//要素のクリア
void SORT_LIST_Clear(
	SORT_LIST_HANDLE handle				//[IN]SORT_LIST_CreateHandleの戻り値
);



//汎用比較用関数
//int用
int SORT_LIST_COMPDEF_int(void* item1, void* item2);

//__int64*（64bit型変数）用
int SORT_LIST_COMPDEF_int64p(void* item1, void* item2);

//char*用strcmpで比較
int SORT_LIST_COMPDEF_strcmp(void* item1, void* item2);

//char*用stricmpで比較
int SORT_LIST_COMPDEF_stricmp(void* item1, void* item2);

//汎用delete関数
//freeのみで解放
void SORT_LIST_DELDEF_free(void* item1);

#ifdef __cplusplus
}
#endif

#endif
