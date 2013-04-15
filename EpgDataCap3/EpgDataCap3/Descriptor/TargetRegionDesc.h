#pragma once

/*
6.2.27 対象地域記述子（Target region descriptor）
対象地域記述子（表6－46 参照）は、番組、もしくは番組を構成する一部のストリーム
が対象とする地域を記述するために使用される。

target_region_descriptor(){
	descriptor_tag		8 uimsbf
	descriptor_length	8 uimsbf
	region_spec_type	8 uimsbf
	target_region_spec()
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
broadcasting_flag（放送／非放送種別）：これは2 ビットのフィールドで、表6－35 に従
って放送／非放送を示す。
broadcasting_identifier（放送の標準方式種別）：これは6 ビットのフィールドで、表6
－36 に従って放送の標準方式を示す。
region_spec_type（地域記述方式指定）：この8 ビットのフィールドは、後続の
target_region_spec()構造体における地域記述の方式を指定し、表6－47 に従って符号化さ
れる。
target_region_spec()（地域指定子）：地域記述方式指定ごとに規定される地域指定のため
のデータ構造を示す。（付録G 参照）

bs_prefecture_spec(){
	prefecture_bitmap	56 bslbf
}
prefecture_bitmap（県域指定ビットマップ）：この56 ビットのフィールドは表G－2 に
示すビットマップである。値1 が指定されたビットは当該地域が対象であることを示し、
値0 が指定されたビットは当該地域が対象外であることを示す。

*/

#include "../../../Common/Util.h"

class CTargetRegionDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE region_spec_type;
	BYTE prefecture_bitmap[7];
public:
	CTargetRegionDesc(void);
	~CTargetRegionDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
