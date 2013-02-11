#pragma once

/*
6.2.6 衛星分配システム記述子（Satellite delivery system descriptor）
衛星分配システム記述子は、衛星伝送路の物理的条件を示す。表6－8 参照。

satellite_delivery_system_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	frequency				32 bslbf
	orbital_position		16 bslbf
	west_east_flag			1 bslbf
	polarisation			2 bslbf
	modulation				5 bslbf
	symbol_rate				28 bslbf
	FEC_inner				4 bslbf
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
frequency（周波数）：これは32 ビットのフィールドで、4 ビットBCD コード8 桁で周波
数を表す。衛星分配システム記述子では、周波数は4 桁目以降が小数点以下となるGHz
単位で符号化される。（例 012.73300GHz）
orbital_position（軌道）：これは16 ビットのフィールドで、4 ビットBCD コード4 桁で、
４桁目が小数点以下となる度単位で軌道位置を表す。（例 144.0 度）
west_east_flag（東経西経フラグ）：これは1 ビットのフィールドで、衛星位置が軌道の
東経あるいは西経のどちらになるかを示す。「0」は西経、「1」は東経に位置することを
示す。
polarisation（偏波）：これは2 ビットのフィールドで、表6－9 に従って伝送信号の偏波
を示す。第1 ビットは直線偏波か円偏波かを規定する。
modulation（変調）：これは5 ビットのフィールドで、表6－10 に従って衛星分配システ
ムで使用される変調方式を示す。
symbol_rate（シンボルレート）：これは28 ビットフィールドで、4 ビットBCD コード7
桁で、4 桁目以降が小数点以下となるMsymbol/s 単位でシンボルレート値を表す。（例
021.0960）
FEC_inner（FEC（内符号））：これは4 ビットのフィールドで、表6－11 に従って内符
号を表す。
*/

#include "../../../Common/Util.h"

class CSatelliteDeliverySysDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	double frequency;
	double orbital_position;
	BYTE west_east_flag;
	BYTE polarisation;
	BYTE modulation;
	double symbol_rate;
	BYTE FEC_inner;

public:
	CSatelliteDeliverySysDesc(void);
	~CSatelliteDeliverySysDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
