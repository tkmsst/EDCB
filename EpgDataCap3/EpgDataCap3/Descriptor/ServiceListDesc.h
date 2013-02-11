#pragma once

/*
6.2.14 サービスリスト記述子（Service list descriptor）
サービスリスト記述子（表6－26 参照）は、サービス識別とサービス形式種別によるサ
ービスの一覧を提供する。

service_list_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	for (i=0;i<N;i++){
		service_id				16 uimsbf
		service_type			8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
service_id（サービス識別）：これは16 ビットのフィールドで、そのトランスポートスト
リーム内の情報サービスをユニークに識別する。サービス識別は、対応するプログラムマ
ップセクション内の放送番組番号識別（program_number）に等しい。
service_type（サービス形式種別）：これは８ビットのフィールドで、表6－25 に従って
サービスの種類を表す。
*/

#include "../../../Common/Util.h"

class CServiceListDesc
{
public:
	typedef struct _SERVICE_LIST_DATA{
		WORD service_id;
		BYTE service_type;
	} SERVICE_LIST_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	vector<SERVICE_LIST_DATA> serviceList;

public:
	CServiceListDesc(void);
	~CServiceListDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
