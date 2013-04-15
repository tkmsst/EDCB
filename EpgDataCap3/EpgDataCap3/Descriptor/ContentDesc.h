#pragma once

/*
6.2.4 コンテント記述子（Content descriptor）
コンテント記述子（表6－6 参照）はイベントのジャンルを示すものである。

content_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	for (i=0;i<N;i++) {
		content_nibble_level_1	4 uimsbf
		content_nibble_level_2	4 uimsbf
		user_nibble				4 uimsbf
		user_nibble				4 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
content_nibble_level_1（ジャンル1）：この4 ビットのフィールドは、コンテント識別の
第一段階分類を表す。符号化については別途規定する。（付録H 参照）
content_nibble_level_2（ジャンル2）：この4 ビットのフィールドは、コンテント識別の
第二段階分類を表す。符号化については別途規定する。（付録H 参照）
user_nibble（ユーザジャンル）：この4 ビットのフィールドは、放送事業者により定義さ
れる。

*/

#include "../../../Common/Util.h"

class CContentDesc
{
public:
	typedef struct _NIBBLE_DATA{
		BYTE content_nibble_level_1;
		BYTE content_nibble_level_2;
		BYTE user_nibble_1;
		BYTE user_nibble_2;
	}NIBBLE_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	vector<NIBBLE_DATA> nibbleList;

public:
	CContentDesc(void);
	~CContentDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
