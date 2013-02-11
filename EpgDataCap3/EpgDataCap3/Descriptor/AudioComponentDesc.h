#pragma once

/*
6.2.26 音声コンポーネント記述子（Audio component descriptor）
音声コンポーネント記述子は、音声エレメンタリーストリームの各パラメータを示し、
エレメンタリストリームを文字形式で表現するためにも利用される。（表6－42 参照）

audio_component_descriptor (){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	reserved_future_use		4 bslbf
	stream_content			4 uimsbf
	component_type			8 uimsbf
	component_tag			8 uimsbf
	stream_type				8 uimsbf
	simulcast_group_tag		8 bslbf
	ES_multi_lingual_flag	1 bslbf
	main_component_flag		1 bslbf
	quality_indicator		2 bslbf
	sampling_rate			3 uimsbf
	reserved_future_use		1 bslbf
	ISO_639_language_code	24 bslbf
	if (ES_multi_lingual_flag == 1){
		ISO_639_language_code_2		24 bslbf
	}
	for(i=0;i<N;i++){
		text_char					8 uimsbf
	}
}

broadcasting_flag（放送／非放送種別）：これは2 ビットのフィールドで、表6－35 に従
って放送／非放送を示す。
broadcasting_identifier（放送の標準方式種別）：これは6 ビットのフィールドで、表6
－36 に従って放送の標準方式を示す。
stream_content（コンポーネント内容）：この4 ビットのフィールドは、ストリームの種
別を表す。音声ストリームに対しては「0x02」と設定する。（表6－5 参照）
component_type（コンポーネント種別）：この8 ビットのフィールドは、音声コンポーネ
ントの種別を規定し、表6－43 に従って符号化される。
component_tag（コンポーネントタグ）：これは8 ビットのフィールドである。コンポー
ネントタグは、コンポーネントストリームを識別するためのラベルであり、ストリーム識
別記述子（6.2.16 項参照）内のコンポーネントタグと同一の値である。（ただし、ストリ
ーム識別記述子がPMT 内に存在する場合。）
stream_type（ストリーム形式種別）：この8 ビットのフィールドは、音声ストリームの
形式（MPEG2 BC Audio、AAC Audio）を表す。（付録E 参照）
simulcast_group_tag（サイマルキャストグループ識別）：この8 ビットのフィールドは、
サイマルキャスト（同一内容を異なる符号化方式で伝送）を行なっているコンポーネント
に対して同じ番号を与える。サイマルキャストを行なっていないコンポーネントに対して
は、「0xFF」に設定する。
ES_multi_lingual_flag（ES 多言語フラグ）：この1 ビットのフラグは、1/0+1/0 モードに
おいて、ES 内で2 言語（ES 多言語モード）多重が行われている場合に「1」に設定する。
それ以外のモードの場合には未定義とする。
main_component_flag（主コンポーネントフラグ）：この1 ビットのフラグは、その音声
コンポーネントが主音声であるとき「1」とする。また、1/0+1/0 モードの場合には、第1
音声コンポーネントが主音声であるとき「1」とする。
quality_indicator（音質表示）：この2 ビットのフィールドは音質モードを表し、表6-44
に従って符号化される。
sampling_rate（サンプリング周波数）：この3 ビットのフィールドは、サンプリング周波
数を示し、表6－45 に従って符号化される。
ISO_639_language_code（言語コード）：この24 ビットのフィールドは、音声コンポー
ネントの言語を示す。ES 多言語モードのときは、第1 音声コンポーネントの言語を示す。
言語コードは、ISO 639-2(22)に規定されるアルファベット3 文字コードで表す。各文字は
ISO 8859-1(24)に従って8 ビットで符号化され、その順で24 ビットフィールドに挿入され
る。
例： 日本語はアルファベット3 文字コードで「jpn」であり、次のように符号化される。
「0110 1010 0111 0000 0110 1110」
ISO_639_language_code_2（言語コードその2）：この24 ビットのフィールドは、ES 多
言語モードにおいて、第2 音声コンポーネントの言語を示す。
text_char（コンポーネント記述）：これは8 ビットのフィールドである。一連の文字情報
フィールドは、コンポーネントストリームの文字記述を規定する。文字情報の符号化に関
しては、付録A を参照。

*/

#include "../../../Common/Util.h"

class CAudioComponentDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE stream_content;
	BYTE component_type;
	BYTE component_tag;
	BYTE stream_type;
	BYTE simulcast_group_tag;
	BYTE ES_multi_lingual_flag;
	BYTE main_component_flag;
	BYTE quality_indicator;
	BYTE sampling_rate;
	CHAR ISO_639_language_code[4];
	CHAR ISO_639_language_code2[4];
	BYTE text_charLength;
	CHAR* text_char;
public:
	CAudioComponentDesc(void);
	~CAudioComponentDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
