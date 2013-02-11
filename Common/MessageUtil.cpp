#include "stdafx.h"
#include "CommonDef.h"
#include "StringUtil.h"
#include "MessageUtil.h"

map<wstring, wstring> stringMap;

typedef struct _MESSAGE_TABLE{
	wstring key;
	wstring message;
} MESSAGE_TABLE;

static MESSAGE_TABLE messageTable[]={
	{L"RecStatusEnd",		L"録画終了"},
	{L"RecStatusErrWake",	L"録画失敗 録画開始時間にEpgTimerSrv.exeが起動していなかった可能性があります"},
	{L"RecStatusErrOpen",	L"録画失敗 録画開始時間に録画アプリを起動できなかった可能性があります"},
	{L"RecStatusErrFind",	L"録画失敗 番組が放送されなかった可能性があります"},
	{L"RecStatusEndPg",		L"録画終了 EPGデータを確認できなかったためプログラム予約扱いとしました"},
	{L"RecStatusChgTime",	L"予約登録時の開始時間"},
	{L"RecStatusRelay",		L"イベントリレー"}
};

void CreateMap()
{
	//文字列をリストで保持
	//多言語対応とか別ファイルにする場合にこのあたりを変更すれば拡張できるはず
	if( stringMap.size() != 0 ){
		return ;
	}

	size_t num = sizeof(messageTable) / sizeof(struct _MESSAGE_TABLE);
	for( size_t i = 0; i<num; i++ ){
		stringMap.insert(pair<wstring, wstring>(messageTable[i].key, messageTable[i].message));
	}
}

const wchar_t* GetMessageString(const wchar_t* resourceKey)
{
	CreateMap();

	map<wstring, wstring>::iterator itr;
	wstring searchKey;
	searchKey = resourceKey;
	itr = stringMap.find(searchKey);
	
	wstring message = L"";
	if( itr != stringMap.end() ){
		message = itr->second;
	}
	return message.c_str();
}

const wchar_t* GetRecStatusString(DWORD recStatus, SYSTEMTIME startRecEpg)
{
	DWORD mainStatus = recStatus & 0x000000FF;
	DWORD optionStatus = recStatus & 0x0000FF00;
	wstring message = L"";
	switch(mainStatus){
		case REC_STATUS_END:
			message = GetMessageString(L"RecStatusEnd");
			break;
		case REC_STATUS_ERR_WAKE:
			message = GetMessageString(L"RecStatusErrWake");
			break;
		case REC_STATUS_ERR_OPEN:
			message = GetMessageString(L"RecStatusErrOpen");
			break;
		case REC_STATUS_ERR_FIND:
			message = GetMessageString(L"RecStatusErrFind");
			break;
		case REC_STATUS_END_PG:
			message = GetMessageString(L"RecStatusEndPg");
			break;
		default:
			break;
	}
	if( optionStatus != 0 ){
		wstring option = L"";
		switch(optionStatus){
			case REC_STATUS_CHG_TIME:
				Format( option, L" (%s %04d/%02d/%02d %02d:%02d%02d)",
					GetMessageString(L"RecStatusChgTime"),
					startRecEpg.wYear,
					startRecEpg.wMonth,
					startRecEpg.wDay,
					startRecEpg.wHour,
					startRecEpg.wMinute,
					startRecEpg.wSecond
					);
				break;
			case REC_STATUS_RELAY:
				Format( option, L" (%s)", GetMessageString(L"RecStatusRelay") );
				break;
			default:
				break;
		}
		message += option;
	}
	return message.c_str();
}
