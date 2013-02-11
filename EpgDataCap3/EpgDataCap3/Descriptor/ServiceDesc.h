#pragma once

/*
6.2.13 サービス記述子（Service descriptor）
サービス記述子（表6－24 参照）は編成チャンネル名とその事業者名をサービス形式種
別とともに文字符号で表す。

service_descriptor(){
	descriptor_tag					8 uimsbf
	descriptor_length				8 uimsbf
	service_type					8 uimsbf
	service_provider_name_length	8 uimsbf
	for (i=0;i<N;i++){
		char							8 uimsbf
	}
	service_name_length				8 uimsbf
	for (i=0;i<N;i++){
		char							8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
サービス記述子の意味：
service_type（サービス形式種別）：これは８ビットのフィールドで、表6－25 に従って
サービスの種類を表す。
［注］：このフィールドは、総務省告示平21 第88 号(8)では、サービス形式識別子と表現
されている。
service_provider_name_length（事業者名長）：この8 ビットのフィールドは、後続の事
業者名のバイト長を表す。
char（文字符号）：これは8 ビットのフィールドである。一連の文字情報フィールドは、
事業者名あるいはサービス名を表す。文字情報の符号化に関しては、付録A を参照。
service_name_length（サービス名長）：この8 ビットのフィールドは、後続のサービス
名のバイト長を表す。

*/

#include "../../../Common/Util.h"

class CServiceDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE service_type;
	BYTE service_provider_name_length;
	CHAR* char_service_provider_name;
	BYTE service_name_length;
	CHAR* char_service_name;

public:
	CServiceDesc(void);
	~CServiceDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
