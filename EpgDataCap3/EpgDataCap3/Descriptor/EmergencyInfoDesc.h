#pragma once

/*
6.2.24 緊急情報記述子（Emergency information descriptor）
［注］本項目は、総務省告示平21第88号(8)に規定されている。
緊急情報記述子（表6－40 参照）は、無線設備規則第9 条の3 第5 号に規定される緊急
警報信号に準じた信号であり、緊急警報放送を行う場合に用いられる。

emergency_information_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	for (i=0;i<N;i++){
		service_id				16 uimsbf
		start_end_flag			1 bslbf
		signal_level			1 bslbf
		reserved_future_use		6 bslbf
		area_code_length		8 uimsbf
		for (j=0;j<N;j++){
			area_code				12 bslbf
			reserved_future_use		4 bslbf
		}
	}
}

broadcasting_flag（放送／非放送種別）：これは2 ビットのフィールドで、表6－35 に従
って放送／非放送を示す。
broadcasting_identifier（放送の標準方式種別）：これは6 ビットのフィールドで、表6
－36 に従って放送の標準方式を示す。
service_id（サービス識別）：この16 ビットのフィールドは放送番組番号を示す。これは
program_number に等しい。
start_end_flag（開始／終了フラグ）：この1 ビットのフラグは、郵政省告示昭60 第405
号で定められる緊急警報信号のうち、開始信号および終了信号に対応する。このビットが1
の場合、緊急警報信号が開始もしくは放送中であることを示す。このビットが0 の場合、
緊急警報信号が終了したことを示す。
signal_level（信号種別）：この1 ビットのフィールドは、無線局運用規則第138 条の2
に規定される緊急警報信号の種別に対応する。このビットが0 の場合、放送される緊急警
報信号が第１種開始信号であることを示す。このビットが1 の場合、放送される緊急警報
信号が第２種開始信号であることを示す。（付録D 参照）
area_code_length（地域符号長）：これは8 ビットのフィールドで、後続の地域符号のバ
イト長を示す。
area_code（地域符号）：これは12 ビットのフィールドで、無線局運用規則第138 条の3
で定められる地域符号に対応する。地域符号の割り当ては、郵政省告示昭60 第405 号に
規定されるものを使用する。（付録D 参照）
*/

#include "../../../Common/Util.h"

class CEmergencyInfoDesc
{
public:
	typedef struct _EMERGENCY_DATA{
		WORD service_id;
		BYTE start_end_flag;
		BYTE signal_level;
		BYTE area_code_length;
		vector<WORD> area_codeList;
	} EMERGENCY_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	vector<EMERGENCY_DATA*> emergencyList;

public:
	CEmergencyInfoDesc(void);
	~CEmergencyInfoDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
protected:
	void Clear();
};
