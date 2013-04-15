#include "StdAfx.h"
#include "ChSetUtil.h"

#include "../Common/EpgTimerUtil.h"

CChSetUtil::CChSetUtil(void)
{
}


CChSetUtil::~CChSetUtil(void)
{
}

//チャンネル設定ファイルを読み込む
BOOL CChSetUtil::LoadChSet(
	wstring chSet4FilePath,
	wstring chSet5FilePath
	)
{
	BOOL ret = TRUE;
	if( this->chText4.ParseText(chSet4FilePath.c_str()) == FALSE ){
		ret = FALSE;
	}
	if( this->chText5.ParseText(chSet5FilePath.c_str()) == FALSE ){
		ret = FALSE;
	}
	return ret;
}

//チャンネル設定ファイルを保存する
BOOL CChSetUtil::SaveChSet(
	wstring chSet4FilePath,
	wstring chSet5FilePath
	)
{
	//接続待ち
	HANDLE waitEvent = _CreateEvent(FALSE, TRUE, CHSET_SAVE_EVENT_WAIT);
	if( waitEvent == NULL ){
		return FALSE;
	}
	if(WaitForSingleObject(waitEvent, 10000) == WAIT_TIMEOUT){
		CloseHandle(waitEvent);
		return FALSE;
	}

	BOOL ret = TRUE;
	if( this->chText4.SaveChText(chSet4FilePath.c_str()) == FALSE ){
		ret = FALSE;
	}

	//他で更新されてる可能性あるので再読み込み
	CParseChText5 chText5;
	chText5.ParseText(chSet5FilePath.c_str());
	//現在保持している情報を追加
	map<LONGLONG, CH_DATA5>::iterator itr;
	for( itr = this->chText5.chList.begin(); itr != this->chText5.chList.end(); itr++ ){
		chText5.AddCh(itr->second);
	}
	//保存
	if( chText5.SaveChText(chSet5FilePath.c_str()) == FALSE ){
		ret = FALSE;
	}
	//最新版を再読み込み
	this->chText5.ParseText(chSet5FilePath.c_str());

	SetEvent(waitEvent);
	CloseHandle(waitEvent);

	return ret;
}

//チャンネルスキャン用にクリアする
BOOL CChSetUtil::Clear()
{
	this->chText4.chList.clear();
	this->chText5.chList.clear();
	return TRUE;
}

//チャンネル情報を追加する
BOOL CChSetUtil::AddServiceInfo(
	DWORD space,
	DWORD ch,
	wstring chName,
	SERVICE_INFO* serviceInfo
	)
{
	CH_DATA4 item4;

	item4.space = space;
	item4.ch = ch;
	item4.originalNetworkID = serviceInfo->original_network_id;
	item4.transportStreamID = serviceInfo->transport_stream_id;
	item4.serviceID = serviceInfo->service_id;
	if( serviceInfo->extInfo != NULL ){
		item4.serviceType = serviceInfo->extInfo->service_type;
		item4.partialFlag = serviceInfo->extInfo->partialReceptionFlag;
		if( item4.serviceType == 0x01 || item4.serviceType == 0xA5 ){
			item4.useViewFlag = TRUE;
		}else{
			item4.useViewFlag = FALSE;
		}
		item4.serviceName = serviceInfo->extInfo->service_name;
		item4.chName = chName;
		if( serviceInfo->extInfo->ts_name != NULL ){
			item4.networkName = serviceInfo->extInfo->ts_name;
		}else if( serviceInfo->extInfo->network_name != NULL){
			item4.networkName = serviceInfo->extInfo->network_name;
		}
		item4.remoconID = serviceInfo->extInfo->remote_control_key_id;
	}

	this->chText4.AddCh(item4);

	CH_DATA5 item5;

	item5.originalNetworkID = serviceInfo->original_network_id;
	item5.transportStreamID = serviceInfo->transport_stream_id;
	item5.serviceID = serviceInfo->service_id;
	if( serviceInfo->extInfo != NULL ){
		item5.serviceType = serviceInfo->extInfo->service_type;
		item5.partialFlag = serviceInfo->extInfo->partialReceptionFlag;
		item5.serviceName = serviceInfo->extInfo->service_name;
		if( serviceInfo->extInfo->ts_name != NULL ){
			item5.networkName = serviceInfo->extInfo->ts_name;
		}else if( serviceInfo->extInfo->network_name != NULL){
			item5.networkName = serviceInfo->extInfo->network_name;
		}
		if( item5.serviceType == 0x01 || item4.serviceType == 0xA5 ){
			item5.epgCapFlag = TRUE;
			item5.searchFlag = TRUE;
		}else{
			item5.epgCapFlag = FALSE;
			item5.searchFlag = FALSE;
		}
	}

	this->chText5.AddCh(item5);

	return TRUE;
}


//サービス一覧を取得する
BOOL CChSetUtil::GetEnumService(
	vector<CH_DATA4>* serviceList
	)
{
	if( this->chText4.chList.size() == 0 ){
		return FALSE;
	}
	multimap<LONGLONG, CH_DATA4>::iterator itr;
	for( itr = this->chText4.chList.begin(); itr != this->chText4.chList.end(); itr++ ){
		serviceList->push_back(itr->second);
	}
	return TRUE;
}

//IDから物理チャンネルを検索する
BOOL CChSetUtil::GetCh(
	WORD ONID,
	WORD TSID,
	DWORD& space,
	DWORD& ch
	)
{
	multimap<LONGLONG, CH_DATA4>::iterator itr;
	for( itr = this->chText4.chList.begin(); itr != this->chText4.chList.end(); itr++ ){
		if( itr->second.originalNetworkID == ONID && itr->second.transportStreamID == TSID ){
			space = itr->second.space;
			ch = itr->second.ch;
			return TRUE;
		}
	}
	return FALSE;
}

//EPG取得対象のサービス一覧を取得する
//戻り値：
// エラーコード
//引数：
// chList		[OUT]EPG取得するチャンネル一覧
void CChSetUtil::GetEpgCapService(
	vector<EPGCAP_SERVICE_INFO>* chList
	)
{
	map<ULONGLONG, ULONGLONG> addMap;
	multimap<LONGLONG, CH_DATA4>::iterator itrCh4;
	for( itrCh4 = this->chText4.chList.begin(); itrCh4 != this->chText4.chList.end(); itrCh4++ ){
		LONGLONG key = _Create64Key(itrCh4->second.originalNetworkID, itrCh4->second.transportStreamID, itrCh4->second.serviceID);
		map<LONGLONG, CH_DATA5>::iterator itrCh5;
		itrCh5 = this->chText5.chList.find(key);

		if( itrCh5 != this->chText5.chList.end() ){
			ULONGLONG addKey = ((ULONGLONG)itrCh4->second.space) << 32 | itrCh4->second.ch;
			map<ULONGLONG, ULONGLONG>::iterator itrAdd;
			itrAdd = addMap.find(addKey);
			if( itrAdd == addMap.end() ){
				if( itrCh5->second.epgCapFlag == TRUE ){
					EPGCAP_SERVICE_INFO item;
					item.ONID = itrCh5->second.originalNetworkID;
					item.TSID = itrCh5->second.transportStreamID;
					item.SID = itrCh5->second.serviceID;
					chList->push_back(item);

					addMap.insert(pair<ULONGLONG, ULONGLONG>(addKey,addKey));
				}
			}
		}
	}
}

BOOL CChSetUtil::IsEpgCapService(
	WORD ONID,
	WORD TSID
	)
{
	map<LONGLONG, CH_DATA5>::iterator itrCh5;
	for( itrCh5 = this->chText5.chList.begin(); itrCh5 != this->chText5.chList.end(); itrCh5++ ){
		if( itrCh5->second.originalNetworkID == ONID &&
			itrCh5->second.transportStreamID == TSID &&
			itrCh5->second.epgCapFlag == TRUE
			){
				return TRUE;
		}
	}
	return FALSE;
}

BOOL CChSetUtil::IsPartial(
	WORD ONID,
	WORD TSID,
	WORD SID
	)
{
	LONGLONG key = _Create64Key(ONID, TSID, SID);
	map<LONGLONG, CH_DATA5>::iterator itr;
	itr = this->chText5.chList.find(key);
	if( itr != this->chText5.chList.end() ){
		if( itr->second.partialFlag == 1 ){
			return TRUE;
		}
	}
	return FALSE;
}

