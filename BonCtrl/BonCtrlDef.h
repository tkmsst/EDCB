#ifndef __BON_CTRL_DEF_H__
#define __BON_CTRL_DEF_H__

#include "../Common/Util.h"

#define MUTEX_UDP_PORT_NAME			TEXT("Global\\EpgDataCap_Bon_UDP_PORT_")
#define MUTEX_TCP_PORT_NAME			TEXT("Global\\EpgDataCap_Bon_TCP_PORT_")
#define CHSET_SAVE_EVENT_WAIT		 _T("Global\\EpgTimer_ChSet")


//BonDriverのファイルパス情報
typedef struct _BON_DRIVER_INFO{
	wstring filePath;	//BonDriver.dllのファイルパス
	wstring fileName;	//BonDriver.dllのファイル名（拡張子含む）
	wstring fileTitle;	//BonDriver.dllのファイル名（拡張子含まない）
	_BON_DRIVER_INFO(void){
		filePath = L"";
		fileName = L"";
		fileTitle = L"";
	}
	//=オペレーターの処理
	_BON_DRIVER_INFO & operator= (const _BON_DRIVER_INFO & o) {
		filePath = o.filePath;
		fileName = o.fileName;
		fileTitle = o.fileTitle;
		return *this;
	}
} BON_DRIVER_INFO;

//BonDriverの物理チャンネル情報
typedef struct _BON_CH_INFO{
	wstring chName;		//チャンネル名
	DWORD ch;			//CH
	_BON_CH_INFO(void){
		chName = L"";
		ch = 0;
	}
	//=オペレーターの処理
	_BON_CH_INFO & operator= (const _BON_CH_INFO & o) {
		chName = o.chName;
		ch = o.ch;
		return *this;
	}
}BON_CH_INFO;

//BonDriverのチューナー空間情報
typedef struct _BON_SPACE_INFO{
	wstring spaceName;					//チューナー空間名
	DWORD space;						//Space
	map<DWORD, BON_CH_INFO> chMap;		//チャンネルリスト（キー CH）
	_BON_SPACE_INFO(void){
		spaceName = L"";
		space = 0;
	}
	//=オペレーターの処理
	_BON_SPACE_INFO & operator= (const _BON_SPACE_INFO & o) {
		spaceName = o.spaceName;
		space = o.space;
		chMap = o.chMap;
		return *this;
	}
}BON_SPACE_INFO;

//受信データのバッファリング用
typedef struct _TS_DATA{
	BYTE* data;				//TSデータ
	DWORD size;				//dataのサイズ
	_TS_DATA(void){
		data = NULL;
		size = 0;
	}
	~_TS_DATA(void){
		SAFE_DELETE_ARRAY(data);
	}
} TS_DATA;

//ネットワーク送信用設定
typedef struct _NW_SEND_INFO{
	wstring ipString;
	DWORD ip;
	DWORD port;
	BOOL broadcastFlag;
}NW_SEND_INFO;

//サービス情報
typedef struct _TS_SERVICE_INFO{
	WORD ONID;
	WORD TSID;
	WORD SID;
	BYTE serviceType;
	BOOL partialFlag;
	wstring serviceName;
	wstring networkName;
	BYTE remoteControlKeyID;
}TS_SERVICE_INFO;

//EPG取得用サービス情報
typedef struct _EPGCAP_SERVICE_INFO{
	WORD ONID;
	WORD TSID;
	WORD SID;
}EPGCAP_SERVICE_INFO;


#endif
