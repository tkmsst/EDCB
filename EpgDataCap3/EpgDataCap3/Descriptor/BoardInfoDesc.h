#pragma once

/*
6.2.39 掲示板情報記述子（Board information descriptor）
掲示板情報記述子は掲示板情報のタイトルおよび内容をテキスト形式で表す。表6－76
参照。

board_information_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	title_length			8 uimsbf
	for (i=0;i<title_length;i++){
		title_char				8 uimsbf
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
title_length（タイトル長）：この8 ビットのフィールドは、後続のタイトルのバイト長を
表す。
title_char（タイトル）：これは8 ビットのフィールドである。一連の文字情報フィールド
は、掲示板情報タイトルを表す。文字情報の符号化に関しては、付録A を参照。
text_length（内容記述長）：この8 ビットのフィールドは、後続の内容記述のバイト長を
表す。
text_char（内容記述）：これは8 ビットのフィールドである。一連の文字情報フィールド
は掲示板情報の内容を記述する。文字情報の符号化に関しては、付録A を参照。

*/

#include "../../../Common/Util.h"

class CBoardInfoDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE title_length;
	CHAR* title_char;
	BYTE text_length;
	CHAR* text_char;
public:
	CBoardInfoDesc(void);
	~CBoardInfoDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
