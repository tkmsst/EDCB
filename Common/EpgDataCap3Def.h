#ifndef __EPG_DATA_CAP3_DEF_H__
#define __EPG_DATA_CAP3_DEF_H__

#include "Util.h"

//EPGデータ取得ステータス
typedef enum{
	EpgNoData			= 0x0000,	//データがない
	EpgNeedData			= 0x0001,	//たまっていない
	EpgBasicAll			= 0x0010,	//基本情報はたまった
	EpgExtendAll		= 0x0020,	//拡張情報はたまった
	EpgHEITAll			= 0x0040,	//基本、拡張共にたまった
	EpgLEITAll			= 0x0080,	//ワンセグがたまった
} EPG_SECTION_STATUS;

//EPG基本情報
typedef struct _EPG_SHORT_EVENT_INFO{
	WORD event_nameLength;		//event_nameの文字数
	WCHAR* event_name;			//イベント名
	WORD text_charLength;		//text_charの文字数
	WCHAR* text_char;			//情報
	_EPG_SHORT_EVENT_INFO(void){
		event_name = NULL;
		text_char = NULL;
	};
	~_EPG_SHORT_EVENT_INFO(void){
		SAFE_DELETE_ARRAY(event_name);
		SAFE_DELETE_ARRAY(text_char);
	};
} EPG_SHORT_EVENT_INFO;

//EPG拡張情報
typedef struct _EPG_EXTENDED_EVENT_INFO{
	WORD text_charLength;		//text_charの文字数
	WCHAR* text_char;			//詳細情報
	_EPG_EXTENDED_EVENT_INFO(void){
		text_char = NULL;
	};
	~_EPG_EXTENDED_EVENT_INFO(void){
		SAFE_DELETE_ARRAY(text_char);
	};
} EPG_EXTENDED_EVENT_INFO;

//EPGジャンルデータ
typedef struct _EPG_CONTENT_DATA{
	BYTE content_nibble_level_1;
	BYTE content_nibble_level_2;
	BYTE user_nibble_1;
	BYTE user_nibble_2;
}EPG_CONTENT;

//EPGジャンル情報
typedef struct _EPG_CONTENT_INFO{
	WORD listSize;
	EPG_CONTENT* nibbleList;
	_EPG_CONTENT_INFO(void){
		listSize = 0;
		nibbleList = NULL;
	};
	~_EPG_CONTENT_INFO(void){
		SAFE_DELETE_ARRAY(nibbleList);
	};
} EPG_CONTEN_INFO;

//EPG映像情報
typedef struct _EPG_COMPONENT_INFO{
	BYTE stream_content;
	BYTE component_type;
	BYTE component_tag;
	WORD text_charLength;		//text_charの文字数
	WCHAR* text_char;			//詳細情報
	_EPG_COMPONENT_INFO(void){
		text_char = NULL;
	};
	~_EPG_COMPONENT_INFO(void){
		SAFE_DELETE_ARRAY(text_char);
	};
} EPG_COMPONENT_INFO;

//EPG音声情報
typedef struct _EPG_AUDIO_COMPONENT_INFO_DATA{
	BYTE stream_content;
	BYTE component_type;
	BYTE component_tag;
	BYTE stream_type;
	BYTE simulcast_group_tag;
	BYTE ES_multi_lingual_flag;
	BYTE main_component_flag;
	BYTE quality_indicator;
	BYTE sampling_rate;
	WORD text_charLength;		//text_charの文字数
	WCHAR* text_char;			//詳細情報
	_EPG_AUDIO_COMPONENT_INFO_DATA(void){
		text_char = NULL;
	};
	~_EPG_AUDIO_COMPONENT_INFO_DATA(void){
		SAFE_DELETE_ARRAY(text_char);
	};
} EPG_AUDIO_COMPONENT_INFO_DATA;

//EPG音声情報
typedef struct _EPG_AUDIO_COMPONENT_INFO{
	WORD listSize;
	EPG_AUDIO_COMPONENT_INFO_DATA* audioList;
	_EPG_AUDIO_COMPONENT_INFO(void){
		listSize = 0;
		audioList = NULL;
	};
	~_EPG_AUDIO_COMPONENT_INFO(void){
		SAFE_DELETE_ARRAY(audioList);
	};
} EPG_AUDIO_COMPONENT_INFO;

//EPGイベントデータ
typedef struct _EPG_EVENT_DATA{
	WORD original_network_id;
	WORD transport_stream_id;
	WORD service_id;
	WORD event_id;
}EPG_EVENT_DATA;

//EPGイベントグループ情報
typedef struct _EPG_EVENTGROUP_INFO{
	BYTE group_type;
	BYTE event_count;
	EPG_EVENT_DATA* eventDataList;
	_EPG_EVENTGROUP_INFO(void){
		eventDataList = NULL;
	};
	~_EPG_EVENTGROUP_INFO(void){
		SAFE_DELETE_ARRAY(eventDataList);
	};
} EPG_EVENTGROUP_INFO;

typedef struct _EPG_EVENT_INFO{
	WORD event_id;							//イベントID
	BYTE StartTimeFlag;						//start_timeの値が有効かどうか
	SYSTEMTIME start_time;					//開始時間
	BYTE DurationFlag;						//durationの値が有効かどうか
	DWORD durationSec;						//総時間（単位：秒）

	EPG_SHORT_EVENT_INFO* shortInfo;		//基本情報
	EPG_EXTENDED_EVENT_INFO* extInfo;		//拡張情報
	EPG_CONTEN_INFO* contentInfo;			//ジャンル情報
	EPG_COMPONENT_INFO* componentInfo;		//映像情報
	EPG_AUDIO_COMPONENT_INFO* audioInfo;	//音声情報
	EPG_EVENTGROUP_INFO* eventGroupInfo;	//イベントグループ情報
	EPG_EVENTGROUP_INFO* eventRelayInfo;	//イベントリレー情報

	BYTE freeCAFlag;						//ノンスクランブルフラグ
	_EPG_EVENT_INFO(void){
		shortInfo = NULL;
		extInfo = NULL;
		contentInfo = NULL;
		componentInfo = NULL;
		audioInfo = NULL;
		eventGroupInfo = NULL;
		eventRelayInfo = NULL;
		freeCAFlag = 0;
	};
	~_EPG_EVENT_INFO(void){
		SAFE_DELETE(shortInfo);
		SAFE_DELETE(extInfo);
		SAFE_DELETE(contentInfo);
		SAFE_DELETE(componentInfo);
		SAFE_DELETE(audioInfo);
		SAFE_DELETE(eventGroupInfo);
		SAFE_DELETE(eventRelayInfo);
	};
}EPG_EVENT_INFO;

//サービスの詳細情報
typedef struct _SERVICE_EXT_INFO{
	BYTE service_type;
	BYTE partialReceptionFlag;
	WCHAR* service_provider_name;
	WCHAR* service_name;
	WCHAR* network_name;
	WCHAR* ts_name;
	BYTE remote_control_key_id;
	_SERVICE_EXT_INFO(void){
		service_type = 0;
		partialReceptionFlag = FALSE;
		service_provider_name = NULL;
		service_name = NULL;
		network_name = NULL;
		ts_name = NULL;
		remote_control_key_id = 0;
	};
	~_SERVICE_EXT_INFO(void){
		SAFE_DELETE_ARRAY(service_provider_name);
		SAFE_DELETE_ARRAY(service_name);
		SAFE_DELETE_ARRAY(network_name);
		SAFE_DELETE_ARRAY(ts_name);
	};
}SERVICE_EXT_INFO;

//サービス情報
typedef struct _SERVICE_INFO{
	WORD original_network_id;	//original_network_id
	WORD transport_stream_id;	//transport_stream_id
	WORD service_id;			//service_id
	SERVICE_EXT_INFO* extInfo;	//詳細情報
	_SERVICE_INFO(void){
		extInfo = NULL;
	};
	~_SERVICE_INFO(void){
		SAFE_DELETE(extInfo);
	};
}SERVICE_INFO;

#endif
