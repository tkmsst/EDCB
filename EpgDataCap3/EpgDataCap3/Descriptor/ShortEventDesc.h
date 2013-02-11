#pragma once

/*
6.2.15 短形式イベント記述子（Short event descriptor）
短形式イベント記述子はイベント名およびそのイベントの短い記述をテキスト形式で表
す。表6－27 参照。

short_event_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	ISO_639_language_code	24 bslbf
	event_name_length		8 uimsbf
	for (i=0;i<event_name_length;i++){
		event_name_char			8 uimsbf
	}
	text_length				8 uimsbf
	for (i=0;i<text_length;i++){
		text_char				8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
ISO_639_language_code（言語コード）：この24 ビットのフィールドは、後続の文字情
報フィールドの言語をISO 639-2(22)に規定されるアルファベット3 文字コードで表す。各
文字はISO 8859-1(24)に従って8 ビットで符号化され、その順で24 ビットフィールドに挿
入される。
例： 日本語はアルファベット3 文字コードで「jpn」であり、次のように符号化される。
「0110 1010 0111 0000 0110 1110」
event_name_length（番組名長）：この8 ビットのフィールドは、後続の番組名のバイト
長を表す。
event_name_char（番組名）：これは8 ビットのフィールドである。一連の文字情報フィ
ールドは、番組名を表す。文字情報の符号化に関しては、付録A を参照。
text_length（番組記述長）：この8 ビットのフィールドは、後続の番組記述のバイト長を
表す。
text_char（番組記述）：これは8 ビットのフィールドである。一連の文字情報フィールド
は番組の説明を記述する。文字情報の符号化に関しては、付録A を参照。

*/

#include "../../../Common/Util.h"

class CShortEventDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	CHAR ISO_639_language_code[4];
	BYTE event_name_length;
	CHAR* event_name_char;
	BYTE text_length;
	CHAR* text_char;

public:
	CShortEventDesc(void);
	~CShortEventDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
