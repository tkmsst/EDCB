#pragma once

/*
6.2.2 CA 識別記述子（CA identifier descriptor）
CA 識別記述子（表6－3 参照）は、特定のブーケ、サービス、イベント、あるいはコン
ポーネントが限定受信システムに関係しているかどうかを示し、さらに限定受信方式識別
（CA_system_id）で限定受信システムの種別を示す。

CA_identifier_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	for (i=0;i<N;i++){
		CA_system_id			16 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
CA_system_id（限定受信方式識別）：この16 ビットのフィールドは、CA システムを識
別する。このフィールド値の割当ては、標準化機関の規定による。（付録M 参照）
*/

#include "../../../Common/Util.h"

class CCAIdentifierDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	vector<WORD> CA_system_id_List;

public:
	CCAIdentifierDesc(void);
	~CCAIdentifierDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
