#pragma once

/*
6.2.36 ブロードキャスタ名記述子（Broadcaster name descriptor）
ブロードキャスタ名記述子は、ブロードキャスタの名称を記述する。表6－70 参照。

broadcaster_name_descriptor(){
	descriptor_tag		8 uimsbf
	descriptor_length	8 uimsbf
	for(i=0; i<N; i++){
		char				8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
char（文字符号）：これは8 ビットのフィールドである。一連の文字情報フィールドは、
ブロードキャスタ名を表す。文字情報の符号化に関しては、付録A を参照。

*/

#include "../../../Common/Util.h"

class CBroadcasterNameDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE char_nameLength;
	CHAR* char_name;

public:
	CBroadcasterNameDesc(void);
	~CBroadcasterNameDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
