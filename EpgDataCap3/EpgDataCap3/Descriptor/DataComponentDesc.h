#pragma once

/*
6.2.20 データ符号化方式記述子（Data component descriptor）
［注］本項目は、総務省告示平 21 第88 号(8)に規定されている。
データ符号化方式記述子（表6－32 参照）は、データ符号化方式を識別するために使用
される。

data_component_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	data_component_id		16 uimsbf
	for (i=0;i<N;i++){
		additional_data_component_info	8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
data_component_id（データ符号化方式識別）：この16 ビットのフィールドは、データの
符号化方式を識別するのに使用される。このフィールド値の割当ては、標準化機関の規定
による。
additional_data_component_info（付加識別情報）：これは8 ビットのフィールドで、識
別子番号の拡張、または符号化方式毎に規定される補足情報の格納に使用される。この領
域に記述される情報のデータ構造はデータ符号化方式毎に別途規定する。（付録J 参照）

*/

#include "../../../Common/Util.h"

class CDataComponentDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD data_component_id;
	BYTE additional_data_component_infoLength;
	BYTE* additional_data_component_info;

public:
	CDataComponentDesc(void);
	~CDataComponentDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
