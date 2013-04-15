#pragma once

/*
6.2.11 ネットワーク名記述子（Network name descriptor）
ネットワーク名記述子は文字符号によりネットワーク名を記述する。表6－21 参照。

network_name_descriptor(){
	descriptor_tag		8 uimsbf
	descriptor_length	8 uimsbf
	for (i=0;i<N;i++){
		char				8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
char（文字符号）： これは８ビットのフィールドである。一連の文字符号フィールドでは、
NIT で通知される分配システムの名称が記述される。文書情報の符号化に関しては、付録
Ａを参照。

*/

#include "../../../Common/Util.h"

class CNetworkNameDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE char_nameLength;
	CHAR* char_name;
public:
	CNetworkNameDesc(void);
	~CNetworkNameDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
