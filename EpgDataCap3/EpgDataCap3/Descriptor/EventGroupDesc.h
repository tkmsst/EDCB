#pragma once

/*
6.2.34 イベントグループ記述子（Event group descriptor）
イベントグループ記述子は、複数のイベント間に関係がある場合に、それらのイベント
群がグループ化されていることを示すために用いる。表6－67 参照。

event_group_descriptor (){
	descriptor_tag				8 uimsbf
	descriptor_length			8 uimsbf
	group_type					4 uimsbf
	event_count					4 uimsbf
	for(i=0; i< event_count; i++){
		service_id					16 uimsbf
		event_id					16 uimsbf
	}
	if(group_type == 4 || group_type ==5){
		for(i=0 ;i< N ; i++){
			original_network_id		16 uimsbf
			transport_stream_id		16 uimsbf
			service_id				16 uimsbf
			event_id				16 uimsbf
		}
	}else{
		for(i=0; i< N; i++){
			private_data_byte		8 uimsbf
		}
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
group_type（グループ種別）：これは4 ビットのフィールドで、表6－68 に従い、イベン
トのグループ種別を表す。
event_count（イベントループ数）：これは4 ビットのフィールドで、後続のevent_id ル
ープ数を表す。
service_id（サービス識別）：これは16 ビットのフィールドで、関連付ける情報サービス
のサービス識別を示す。サービス識別は、対応するプログラムマップセクション内の放送
番組番号識別（program_number）に等しい。
event_id（イベント識別）：これは16 ビットのフィールドで、関連付けるイベントのイベ
ント識別を示す。
original_network_id（オリジナルネットワーク識別）：これは１６ビットのフィールドで、
ネットワークをまたがるイベントリレー、イベント移動の際に、関連するイベントが伝送
されているネットワークの識別値を示す。
transport_stream_id（トランスポートストリーム識別）：これは、１６ビットのフィール
ドでネットワークをまたがるイベントリレー、イベント移動の際に、関連するイベントが
伝送されているトランスポートストリームの識別値を示す。

*/

#include "../../../Common/Util.h"

class CEventGroupDesc
{
public:
	typedef struct _EVENT_DATA{
		WORD service_id;
		WORD event_id;
	}EVENT_DATA;
	typedef struct _EVENT_DATA2{
		WORD original_network_id;
		WORD transport_stream_id;
		WORD service_id;
		WORD event_id;
	}EVENT_DATA2;
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE group_type;
	BYTE event_count;
	vector<EVENT_DATA> eventDataList;
	vector<EVENT_DATA2> eventData2List;
	BYTE private_data_byteLength;
	BYTE* private_data_byte;

public:
	CEventGroupDesc(void);
	~CEventGroupDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
