#pragma once

/*
6.2.17 スタッフ記述子（Stuffing descriptor）
スタッフ記述子は、前に符号化された記述子を無効にしたりテーブルのスタッフィング
のためのダミー記述子の挿入に利用される。表6－29 参照。

stuffing_descriptor(){
	descriptor_tag		8 uimsbf
	descriptor_length	8 uimsbf
	for (i= 0;i<N;i++){
		stuffing_byte		8 bslbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
stuffing_byte（スタッフィングバイト）：これは8 ビットのフィールドである。このフィ
ールドは毎回異なる値に設定可能である。受信機ではスタッフィングバイトは廃棄される。

*/

#include "../../../Common/Util.h"

class CStuffingDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE stuffing_byteLength;
	BYTE* stuffing_byte;
public:
	CStuffingDesc(void);
	~CStuffingDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
