#pragma once

/*
6.2.16 ストリーム識別記述子（Stream identifier descriptor）
PMT 内で使用されるストリーム識別記述子（表6－28 参照）は、サービスのコンポーネ
ントストリームにラベルを付け、このラベルによってEIT 内のコンポーネント記述子で示
される記述内容（表6－5）（例えば、あるサービスのコンポーネントストリームは「映像、
アスペクト比16:9 パンベクトルあり」であること）を参照できるために使用する。ストリ
ーム識別記述子は、関係するES 情報長フィールドの直後に置く。

stream_identifier_descriptor(){
	descriptor_tag		8 uimsbf
	descriptor_length	8 uimsbf
	component_tag		8 uimsbf
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
component_tag（コンポーネントタグ）：サービスのコンポーネントストリームは、この8
ビットのフィールドにより、コンポーネント記述子で示される記述内容（表6－5）を参照
できる。プログラムマップセクションでは、各ストリームに与えるコンポーネントタグの
値は異なる値とすべきである。

*/

#include "../../../Common/Util.h"

class CStreamIdentifierDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE component_tag;

public:
	CStreamIdentifierDesc(void);
	~CStreamIdentifierDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
