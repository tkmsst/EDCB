#pragma once

/*
6.2.19 タイムシフトサービス記述子（Time shifted service descriptor）
この記述子は、サービス記述子の代わりに使われ、他のサービスのタイムシフトされた
コピーのサービスを表す。表6－31 参照。

time_shifted_service_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	reference_service_id	16 uimsbf
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
reference_service_id（基準サービス識別）：この16 ビットのフィールドは、NVOD を構
成しているサービスの基準サービスを示す。基準サービスは、常にこのトランスポートス
トリーム中にある。ここではサービス識別はプログラムマップセクション内の対応する放
送番組番号識別を持たない。
*/

#include "../../../Common/Util.h"

class CTimeShiftedServiceDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD reference_service_id;
public:
	CTimeShiftedServiceDesc(void);
	~CTimeShiftedServiceDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
