#pragma once

/*
6.2.31 地上分配システム記述子（Terrestrial delivery system descriptor）
地上分配システム記述子は、地上伝送路の物理的条件を示す。表6－61 参照。

terrestrial_delivery_system_descriptor(){
	descriptor_tag		8 uimsbf
	descriptor_length	8 uimsbf
	area_code			12 bslbf
	guard_interval		2 bslbf
	transmission_mode	2 bslbf
	for(i=0; i<N; i++){
		frequency			16 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
area_code（エリアコード）：この12 ビットのフィールドは、サービスエリアのコードを
示す。
guard_interval（ガードインターバル）：これは2 ビットのフィールドで、表6－62 に従
ってガードインターバルを示す。
transmission_mode（モード情報）：これは2 ビットのフィールドで、表6－63 に従って
モード情報を示す。
frequency（周波数）：この16 ビットのフィールドは、中心周波数を示す。周波数単位は
地上デジタル放送方式のチューニングステップと同じ1/7MHz とする。MFN の場合は、
使用周波数を複数列記する。

*/

#include "../../../Common/Util.h"

class CTerrestrialDeliverySysDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD area_code;
	BYTE guard_interval;
	BYTE transmission_mode;
	vector<WORD> frequencyList;

public:
	CTerrestrialDeliverySysDesc(void);
	~CTerrestrialDeliverySysDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
