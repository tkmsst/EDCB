#pragma once

/*
6.2.32 部分受信記述子（Partial reception descriptor）
部分受信記述子は、地上伝送路の部分受信階層で伝送されているサービス識別を記述す
る。表6－64 参照。

partial_reception_descriptor(){
	descriptor_tag		8 uimsbf
	descriptor_length	8 uimsbf
	for(i=0; i<N; i++){
		service_id			16 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
service_id（サービス識別）：これは16 ビットのフィールドで、部分受信階層で伝送され
る情報サービスのサービス識別を示す。サービス識別は、対応するプログラムマップセク
ション内の放送番組番号識別（program_number）に等しい。

*/

#include "../../../Common/Util.h"

class CPartialReceptionDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	vector<WORD> service_idList;
public:
	CPartialReceptionDesc(void);
	~CPartialReceptionDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
