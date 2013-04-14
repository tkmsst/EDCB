#pragma once

/*
6.2.23 デジタルコピー制御記述子（Digital copy control descriptor）
デジタルコピー制御記述子（表6－38 参照）は、デジタル記録機器におけるコピー世代
を制御する情報を示し、デジタル記録が行われることが想定される場合に、放送局（著作
権者側）が番組の記録、コピーに関する情報をデジタル記録機器に伝えるために用いられ
る。また、個々の番組の最大伝送レートを識別するためにも利用される。

digital_copy_control_descriptor(){
	descriptor_tag					8 uimsbf
	descriptor_length				8 uimsbf
	digital_recording_control_data	2 bslbf
	maximum_bitrate_flag			1 bslbf
	component_control_flag			1 bslbf
	user_defined					4 bslbf
	if (maximum_bitrate_flag == 1){
		maximum_bitrate					8 uimsbf
	}
	if (component_control_flag == 1){
		component_control_length		8 uimsbf
		for (i=0;i<N;i++){
			component_tag					8 uimsbf
			digital_recording_control_data	2 bslbf
			maximum_bitrate_flag			1 bslbf
			reserved_future_use				1 bslbf
			user_defined					4 bslbf
			if (maximum_bitrate_flag == 1){
				maximum_bitrate					8 uimsbf
			}
		}
	}
}

broadcasting_flag（放送／非放送種別）：これは2 ビットのフィールドで、表6－35 に従
って放送／非放送を示す。
broadcasting_identifier（放送の標準方式種別）：これは6 ビットのフィールドで、表6
－36 に従って放送の標準方式を示す。
digital_recording_control_data（デジタルコピー制御情報）：この2 ビットのフィールド
は、コピー世代を制御する情報を表し、表6－39 に従って符号化される。
maximum_bit_rate_flag（最大伝送レートフラグ）：この1 ビットのフラグが「1」の場合、
後続の最大伝送レートのフィールドが有効であることを示す。「0」の場合、このフラグの
直後の最大伝送レートのフィールドは存在しない。
component_control_flag（コンポーネント制御フラグ）：この１ビットのフラグは、番組
を構成するコンポーネント毎にデジタルコピー制御情報を規定するかどうかを示す。この
フラグが「1」の場合、コンポーネント制御長以降のフィールドが有効となり、デジタルコ
ピー制御情報は番組を構成するコンポーネント毎に規定される。「0」の場合、デジタルコ
ピー制御情報は番組全体について規定され、コンポーネント制御長以降のフィールドは存
在しない。この記述子をPMT で伝送する場合は、コンポーネント制御フラグは常に「0」
とする。
user_defined（事業者定義ビット）：この4 ビットのフィールドは、放送事業者が独自
に定義することができる。
maximum_bit_rate（最大伝送レート）：この8 ビットのフィールドは、各イベントまた
はエレメンタリーストリームのトランスポートストリームパケットの伝送レートを
1/4Mbps 毎に切り上げて記述する。可変伝送レートの場合は、最大値を記述する。
component_control_length（コンポーネント制御長）：この8 ビットのフィールドは、後
続のコンポーネント制御ループのバイト長を示す。
component_tag（コンポーネントタグ）：これは8 ビットのフィールドである。コンポー
ネントタグは番組を構成するコンポーネントのエレメンタリーストリームを識別するため
のラベルであり、コンポーネント記述子およびストリーム識別記述子内のコンポーネント
タグと同一の値である。

*/

#include "../../../Common/Util.h"

class CDigitalCopyCtrlDesc
{
public:
	typedef struct _COMPONENT_CTRL_DATA{
		BYTE component_tag;
		BYTE digital_recording_control_data;
		BYTE maximum_bitrate_flag;
		BYTE user_defined;
		BYTE maximum_bitrate;
	} COMPONENT_CTRL_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE digital_recording_control_data;
	BYTE maximum_bitrate_flag;
	BYTE component_control_flag;
	BYTE user_defined;
	BYTE maximum_bitrate;
	BYTE component_control_length;
	vector<COMPONENT_CTRL_DATA> component_controlList;

public:
	CDigitalCopyCtrlDesc(void);
	~CDigitalCopyCtrlDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
