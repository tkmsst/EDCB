#pragma once

/*
6.2.21 システム管理記述子（System management descriptor）
［注］本項目は、総務省告示平 21 第88 号(8)に規定されている。
システム管理記述子（表6－33 参照）は、放送と非放送を識別するために使用される。

system_management_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	system_management_id	16 uimsbf
	for (i=0;i <N;i++){
		additional_identification_info	8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
system_management_id（システム管理識別）：これは16 ビットのフィールドで、表6
－34 に示す構成からなる。
additional_identification_info（付加識別情報）：これは8 ビットのフィールドで、システ
ム管理識別の番号の拡張に使用される。

system_management_id(){
	broadcasting_flag						2 uimsbf
	broadcasting_identifier					6 uimsbf
	additional_broadcasting_identification	8 uimsbf
}

broadcasting_flag（放送／非放送種別）：これは2 ビットのフィールドで、表6－35 に従
って放送／非放送を示す。
broadcasting_identifier（放送の標準方式種別）：これは6 ビットのフィールドで、表6
－36 に従って放送の標準方式を示す。
additional_broadcasting_identification（詳細の識別）：これは8 ビットのフィールドで、
事業者の運用規定で定める。

*/

#include "../../../Common/Util.h"

class CSystemManagementDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD system_management_id;
	BYTE additional_identification_infoLength;
	BYTE* additional_identification_info;
public:
	CSystemManagementDesc(void);
	~CSystemManagementDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
