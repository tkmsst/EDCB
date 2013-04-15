// EpgDataCap3.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"

#include "EpgDataCap3Main.h"
#include "../../Common/ErrDef.h"

map<DWORD, CEpgDataCap3Main*> g_List;
DWORD g_nextID = 1;

DWORD GetNextID()
{
	DWORD nextID = 0xFFFFFFFF;

	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(g_nextID);
	if( itr == g_List.end() ){
		nextID = g_nextID;
		g_nextID++;
		if( g_nextID == 0 || g_nextID == 0xFFFFFFFF){
			g_nextID = 1;
		}
	}else{
		for( DWORD i=1; i<0xFFFFFFFF; i++ ){
			itr = g_List.find(g_nextID);
			if( itr == g_List.end() ){
				nextID = g_nextID;
				g_nextID++;
				if( g_nextID == 0 || g_nextID == 0xFFFFFFFF){
					g_nextID = 1;
				}
				break;
			}else{
				g_nextID++;
			}
			if( g_nextID == 0 || g_nextID == 0xFFFFFFFF){
				g_nextID = 1;
			}
		}
	}

	return nextID;
}

//DLLの初期化
//戻り値：
// エラーコード
//引数：
// asyncMode		[IN]TRUE:非同期モード、FALSE:同期モード
// id				[OUT]識別ID
DWORD WINAPI InitializeEP(
	BOOL asyncFlag,
	DWORD* id
	)
{
	if( id == NULL ){
		return ERR_INVALID_ARG;
	}

	CEpgDataCap3Main* main = new CEpgDataCap3Main;
	DWORD err = main->Initialize(asyncFlag);
	if( err == NO_ERR ){
		*id = GetNextID();
		g_List.insert(pair<DWORD, CEpgDataCap3Main*>(*id, main));
	}
	return err;
}

//DLLの開放
//戻り値：
// エラーコード
//引数：
// id		[IN]識別ID InitializeEPの戻り値
DWORD WINAPI UnInitializeEP(
	DWORD id
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ERR_NOT_INIT;
	}

	DWORD err = itr->second->UnInitialize();

	SAFE_DELETE(itr->second);

	g_List.erase(itr);

	return err;
}

//解析対象のTSパケット１つを読み込ませる
//戻り値：
// エラーコード
// id		[IN]識別ID InitializeEPの戻り値
// data		[IN]TSパケット１つ
// size		[IN]dataのサイズ（188、192あたりになるはず）
DWORD WINAPI AddTSPacketEP(
	DWORD id,
	BYTE* data,
	DWORD size
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ERR_NOT_INIT;
	}

	return itr->second->AddTSPacket(data, size);
}

//解析データの現在のストリームＩＤを取得する
//戻り値：
// エラーコード
// id						[IN]識別ID
// originalNetworkID		[OUT]現在のoriginalNetworkID
// transportStreamID		[OUT]現在のtransportStreamID
DWORD WINAPI GetTSIDEP(
	DWORD id,
	WORD* originalNetworkID,
	WORD* transportStreamID
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ERR_NOT_INIT;
	}

	return itr->second->GetTSID(originalNetworkID, transportStreamID);
}

//自ストリームのサービス一覧を取得する
//戻り値：
// エラーコード
//引数：
// id						[IN]識別ID
// serviceListSize			[OUT]serviceListの個数
// serviceList				[OUT]サービス情報のリスト（DLL内で自動的にdeleteする。次に取得を行うまで有効）
DWORD WINAPI GetServiceListActualEP(
	DWORD id,
	DWORD* serviceListSize,
	SERVICE_INFO** serviceList
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ERR_NOT_INIT;
	}

	return itr->second->GetServiceListActual(serviceListSize, serviceList);
}

//蓄積されたEPG情報のあるサービス一覧を取得する
//SERVICE_EXT_INFOの情報はない場合がある
//戻り値：
// エラーコード
//引数：
// id						[IN]識別ID
// serviceListSize			[OUT]serviceListの個数
// serviceList				[OUT]サービス情報のリスト（DLL内で自動的にdeleteする。次に取得を行うまで有効）
DWORD WINAPI GetServiceListEpgDBEP(
	DWORD id,
	DWORD* serviceListSize,
	SERVICE_INFO** serviceList
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ERR_NOT_INIT;
	}

	return itr->second->GetServiceListEpgDB(serviceListSize, serviceList);
}

//指定サービスの全EPG情報を取得する
//戻り値：
// エラーコード
//引数：
// id						[IN]識別ID
// originalNetworkID		[IN]取得対象のoriginalNetworkID
// transportStreamID		[IN]取得対象のtransportStreamID
// serviceID				[IN]取得対象のServiceID
// epgInfoListSize			[OUT]epgInfoListの個数
// epgInfoList				[OUT]EPG情報のリスト（DLL内で自動的にdeleteする。次に取得を行うまで有効）
DWORD WINAPI GetEpgInfoListEP(
	DWORD id,
	WORD originalNetworkID,
	WORD transportStreamID,
	WORD serviceID,
	DWORD* epgInfoListSize,
	EPG_EVENT_INFO** epgInfoList
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ERR_NOT_INIT;
	}

	return itr->second->GetEpgInfoList(originalNetworkID, transportStreamID, serviceID, epgInfoListSize, epgInfoList);
}

//指定サービスの現在or次のEPG情報を取得する
//戻り値：
// エラーコード
//引数：
// originalNetworkID		[IN]取得対象のoriginalNetworkID
// transportStreamID		[IN]取得対象のtransportStreamID
// serviceID				[IN]取得対象のServiceID
// nextFlag					[IN]TRUE（次の番組）、FALSE（現在の番組）
// epgInfo					[OUT]EPG情報（DLL内で自動的にdeleteする。次に取得を行うまで有効）
DWORD WINAPI GetEpgInfoEP(
	DWORD id,
	WORD originalNetworkID,
	WORD transportStreamID,
	WORD serviceID,
	BOOL nextFlag,
	EPG_EVENT_INFO** epgInfo
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ERR_NOT_INIT;
	}

	return itr->second->GetEpgInfo(originalNetworkID, transportStreamID, serviceID, nextFlag, epgInfo);
}

//指定イベントのEPG情報を取得する
//戻り値：
// エラーコード
//引数：
// id						[IN]識別ID
// originalNetworkID		[IN]取得対象のoriginalNetworkID
// transportStreamID		[IN]取得対象のtransportStreamID
// serviceID				[IN]取得対象のServiceID
// eventID					[IN]取得対象のEventID
// pfOnlyFlag				[IN]p/fからのみ検索するかどうか
// epgInfo					[OUT]EPG情報（DLL内で自動的にdeleteする。次に取得を行うまで有効）
DWORD WINAPI SearchEpgInfoEP(
	DWORD id,
	WORD originalNetworkID,
	WORD transportStreamID,
	WORD serviceID,
	WORD eventID,
	BYTE pfOnlyFlag,
	EPG_EVENT_INFO** epgInfo
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ERR_NOT_INIT;
	}

	return itr->second->SearchEpgInfo(originalNetworkID, transportStreamID, serviceID, eventID, pfOnlyFlag, epgInfo);
}

//EPGデータの蓄積状態をリセットする
//引数：
// id						[IN]識別ID
void WINAPI ClearSectionStatusEP(
	DWORD id
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ;
	}

	itr->second->ClearSectionStatus();
}

//EPGデータの蓄積状態を取得する
//戻り値：
// ステータス
//引数：
// id						[IN]識別ID
// l_eitFlag				[IN]L-EITのステータスを取得
EPG_SECTION_STATUS WINAPI GetSectionStatusEP(
	DWORD id,
	BOOL l_eitFlag
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return EpgNoData;
	}

	return itr->second->GetSectionStatus(l_eitFlag);
}

//PC時計を元としたストリーム時間との差を取得する
//戻り値：
// 差の秒数
//引数：
// id						[IN]識別ID
int WINAPI GetTimeDelayEP(
	DWORD id
	)
{
	map<DWORD, CEpgDataCap3Main*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return EpgNoData;
	}

	return itr->second->GetTimeDelay();
}