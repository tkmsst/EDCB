#pragma once

/*
6.2.3 コンポーネント記述子（Component descriptor）
コンポーネント記述子はコンポーネントの種別を示し、エレメンタリストリームを文字
形式で表現するためにも利用される

component_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	reserved_future_use		4 bslbf
	stream_content			4 uimsbf
	component_type			8 uimsbf
	component_tag			8 uimsbf
	ISO_639_language_code	24 bslbf
	for (i=0;i<N;i++){
		text_char				8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
stream_content（コンポーネント内容）：この4 ビットのフィールドは、ストリームの種別
（映像、音声、データ）を表し、下記の表6－5 に従って符号化される。
component_type（コンポーネント種別）：この8 ビットのフィールドは、映像、音声、デ
ータといったコンポーネントの種別を規定し、下記の表6－5 に従って符号化される。
component_tag（コンポーネントタグ）：これは8 ビットのフィールドである。コンポーネ
ントタグは、コンポーネントストリームを識別するためのラベルであり、ストリーム識別記
述子（6.2.16 項参照）内のコンポーネントタグと同一の値である。（ただし、ストリーム識
別記述子がPMT 内に存在する場合。）
ISO_639_language_code（言語コード）：この24 ビットのフィールドは、コンポーネント
（音声、あるいはデータ）の言語、およびこの記述子に含まれる文字記述の言語を識別する。
言語コードは、ISO 639-2(22)に規定されるアルファベット3 文字コードで表す。各文字はISO
8859-1(24)に従って8 ビットで符号化され、その順で24 ビットフィールドに挿入される。
例： 日本語はアルファベット3 文字コードで「jpn」であり、次のように符号化される。
「0110 1010 0111 0000 0110 1110」
text_char（コンポーネント記述）：これは8 ビットのフィールドである。一連のコンポーネ
ント記述のフィールドは、コンポーネントストリームの文字記述を規定する。

*/

#include "../../../Common/Util.h"

class CComponentDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE stream_content;
	BYTE component_type;
	BYTE component_tag;
	CHAR ISO_639_language_code[4];
	BYTE text_charLength;
	BYTE* text_char;

public:
	CComponentDesc(void);
	~CComponentDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
