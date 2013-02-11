#pragma once

/*
6.2.40 LDT リンク記述子（LDT linkage descriptor）
LDT リンク記述子は、LDT に集約された情報に対するリンクを記述するために使用され
る。表6－77 参照。

LDT_linkage_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	original_service_id		16 uimsbf
	transport_stream_id		16 uimsbf
	original_network_id		16 uimsbf
	for (i=0;i<N;i++){
		description_id			16 uimsbf
		reserved_future_use		4 uimsbf
		description_type		4 uimsbf
		user_defined			8 bslbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
original_service_id（オリジナルサービス識別）：この16 ビットのフィールドは、リンク
するLDT サブテーブルのオリジナルサービス識別を示す。
transport_stream_id（トランスポートストリーム識別）：この16 ビットのフィールドは、
リンクするLDT サブテーブルが含まれるトランスポートストリーム識別を示す。
original_network_id（オリジナルネットワーク識別）：この16 ビットのフィールドは、
リンクするLDT サブテーブルが含まれる元の分配システムのネットワーク識別を示す。
description_id（記述識別）：この16 ビットのフィールドは、リンクする記述の識別番号
を示す。
description_type（記述形式種別）：この4 ビットのフィールドは、表6－78 に従ってリ
ンク先の記述形式の種別を示す。
user_defined（事業者定義ビット）：この8 ビットのフィールドは、放送事業者が独自に
定義することができる。

*/

#include "../../../Common/Util.h"

class CLDTLinkageDesc
{
public:
	typedef struct _LDT_DATA{
		WORD description_id;
		BYTE description_type;
		BYTE user_defined;
	} LDT_DATA;
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD original_service_id;
	WORD transport_stream_id;
	WORD original_network_id;
	vector<LDT_DATA> LDTList;

public:
	CLDTLinkageDesc(void);
	~CLDTLinkageDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
