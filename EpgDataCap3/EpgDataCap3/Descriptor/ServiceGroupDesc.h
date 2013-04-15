#pragma once

/*
6.2.49 サービスグループ記述子 (Service group descriptor)
サービスグループ記述子（表6-92 参照）は、複数のサービス間に関係がある場合に、そ
れらのサービスがグループ化されていることを示すために用いる。

service_group_descriptor (){
	descriptor_tag 8 uimsbf
	descriptor_length 8 uimsbf
	service_group_type 4 uimsbf
	reserved_future_use 4 uimsbf
	if(service_group_type = = 1){
		for(i=0 ;i< N ; i++){
			primary_service_id 16 uimsbf
			secondary_service_id 16 uimsbf
		}
	}else{
		for(i=0; i< N; i++){
			private_data_byte 8 uimsbf
		}
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
service_group_type（サービスグループ種別）：これは4 ビットのフィールドで、表6－
93 に従い、グループを構成するサービスの種類を表す。
primary_service_id（プライマリサービス識別）：これは16 ビットのフィールドで、関連
付ける第一のサービスのサービス識別を示す。
secondary_service_id（セカンダリサービス識別）：これは16 ビットのフィールドで、関
連付ける第二のサービスのサービス識別を示す。

*/

#include "../../../Common/Util.h"

class CServiceGroupDesc
{
public:
	typedef struct _SERVICE_GROUP_DATA{
		WORD primary_service_id;
		WORD secondary_service_id;
	} SERVICE_GROUP_DATA;
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE service_group_type;
	vector<SERVICE_GROUP_DATA> serviceGroupList;

public:
	CServiceGroupDesc(void);
	~CServiceGroupDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
