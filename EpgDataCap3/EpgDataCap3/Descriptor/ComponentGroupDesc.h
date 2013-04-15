#pragma once

/*
6.2.37 コンポーネントグループ記述子（Component group descriptor）
コンポーネントグループ記述子は、イベント内のコンポーネントの組み合わせを定義し、
識別する。表6－71 参照。

component_group_descriptor (){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	component_group_type	3 uimsbf
	total_bit_rate_flag		1 uimsbf
	num_of_group			4 uimsbf
	for(i=0; i< num_of_group; i++){
		component_group_id		4 uimsbf
		num_of_CA_unit			4 uimsbf
		for(i=0; i< num_of_CA_unit; i++){
			CA_unit_id				4 uimsbf
			num_of_component		4 uimsbf
			for(i=0; i< num_of_ component; i++){
				component_tag			8 uimsbf
			}
		}
		if(total_bit_rate_flag==1){
			total_bit_rate			8 uimsbf
		}
		text_length				8 uimsbf
		for(i=0; i< text_length; i++){
			text_char				8 uimsbf
		}
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
component_group_type（コンポーネントグループ種別）：これは3 ビットのフィールドで、
表6－72 に従い、コンポーネントのグループ種別を表す。
total_bit_rate_flag（総ビットレートフラグ）：これは1 ビットのフラグで、イベント中の
コンポーネントグループ内の総ビットレートの記述状態を示す。このビットが「0」の場合、
コンポーネントグループ内の総ビットレートフィールドが当該記述子中に存在しないこと
を示す。このビットが「1」の場合、コンポーネントグループ内の総ビットレートフィール
ドが当該記述子中に存在することを示す。
num_of_group（グループ数）：これは4 ビットのフィールドで、イベント内でのコンポー
ネントグループの数を示す。
component_group_id（コンポーネントグループ識別）：これは4 ビットのフィールドで、
表6－73 に従い、コンポーネントグループ識別を記述する。
num_of_CA_unit（課金単位数）：これは4 ビットのフィールドで、コンポーネントグル
ープ内での課金／非課金単位の数を示す。
CA_unit_id（課金単位識別）：これは4 ビットのフィールドで、表6－74 に従い、コンポ
ーネントが属する課金単位識別を記述する。
num_of_component（コンポーネント数）：これは4 ビットのフィールドで、当該コンポ
ーネントグループに属し、かつ直前のCA_unit_id で示される課金／非課金単位に属する
コンポーネントの数を示す。
component_tag（コンポーネントタグ）：これは8 ビットのフィールドで、コンポーネン
トグループに属するコンポーネントタグ値を示す。
total_bit_rate（トータルビットレート）：これは8 ビットのフィールドで、コンポーネン
トグループ内のコンポーネントの総ビットレートを、トランスポートストリームパケット
の伝送レートを1/4Mbps 毎に切り上げて記述する。
text_length（コンポーネントグループ記述長）：これは8 ビットのフィールドで、後続の
コンポーネントグループ記述のバイト長を表わす。
text_char（コンポーネントグループ記述）：これは8 ビットのフィールドである。一連の
文字情報フィールドは、コンポーネントグループに関する説明を記述する。文字情報の符
号化に関しては、付録A を参照。

*/

#include "../../../Common/Util.h"

class CComponentGroupDesc
{
public:
	typedef struct _CA_UNIT_DATA{
		BYTE CA_unit_id;
		BYTE num_of_component;
		vector<BYTE> component_tagList;
	} CA_UNIT_DATA;
	typedef struct _COMPONENT_DATA{
		BYTE component_group_id;
		BYTE num_of_CA_unit;
		vector<CA_UNIT_DATA> CAUnitList;
		BYTE total_bit_rate;
		BYTE text_length;
		CHAR* text_char;
		_COMPONENT_DATA(void){
			text_char = NULL;
		}
		~_COMPONENT_DATA(void){
			SAFE_DELETE_ARRAY(text_char);
		}
	} COMPONENT_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE component_group_type;
	BYTE total_bit_rate_flag;
	BYTE num_of_group;
	vector<COMPONENT_DATA*> componentList;

public:
	CComponentGroupDesc(void);
	~CComponentGroupDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );

protected:
	void Clear();
};
