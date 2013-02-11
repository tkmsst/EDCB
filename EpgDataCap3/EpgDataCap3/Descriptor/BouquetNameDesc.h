#pragma once

/*
6.2.1 ブーケ名記述子（Bouquet name descriptor）
ブーケ名記述子はテキスト形式でブーケ名を示す。

bouquet_name_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	for(i=0;i<N;i++){
		char					8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
char（文字符号）：これは8 ビットのフィールドである。一連の文字符号フィールドでは、
BAT サブテーブルで通知されるブーケ名が伝送される。文字情報の符号化に関しては、付
録A を参照。
*/

#include "../../../Common/Util.h"

class CBouquetNameDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE nameLength;
	BYTE* name;

public:
	CBouquetNameDesc(void);
	~CBouquetNameDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );

};
