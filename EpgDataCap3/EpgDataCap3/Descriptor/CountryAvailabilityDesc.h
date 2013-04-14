#pragma once

/*
6.2.5 国別受信可否記述子（Country availability descriptor）
国の様々な組み合わせを識別するために、この記述子は各サービスに2 回記載する事が
できる。1 回目はサービスが受信可能な国あるいは国のグループのリストで、2 回目は受信
不可能なリストを示す。後者のリストは前者を無効にする。記述子が1 つしか使用されず、
さらにこれがそのサービスを受信可能な国を記載している場合は、他の国ではそのサービ
スを受信できないことを示す。記述子が1 つしか使用されず、さらにこれがそのサービス
を受信不可能な国を記載している場合は、他の国ではそのサービスが受信可能なことを示
す。この記述子が存在しない場合は、サービスが受信可能な国は定義されない。表6－7 参
照。

country_availability_descriptor(){
	descriptor_tag				8 uimsbf
	descriptor_length			8 uimsbf
	country_availability_flag	1 bslbf
	reserved_future_use			7 bslbf
	for (i=0;I<N;i++){
		country_code				24 bslbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
country_availability_flag（受信可否フラグ）：この1 ビットのフィールドは、後続の国コ
ードが表す国がサービスの受信が可能か否かを示す。受信可否フラグが「1」に設定されて
いる場合、後続の国コードはサービスの受信が可能である国を示す。「0」に設定されてい
る場合、国コードはサービスの受信が不可能な国を示す。
country_code（国コード）：この24 ビットのフィールドは、ISO 3166-1(23)で規定される
アルファベット3 文字コードを使用して国名を表す。各文字は、ISO 8859-1(24)に従って8
ビットで符号化され、その順で24 ビットフィールドに挿入される。
例： 日本の3 文字コードは「JPN」であり、次のように符号化される。
「0100 1010 0101 0000 0100 1110
*/

#include "../../../Common/Util.h"

class CCountryAvailabilityDesc
{
public:
	typedef struct _COUNTRY_DATA{
		CHAR country_code[4];
	}COUNTRY_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	CHAR country_availability_flag;
	vector<COUNTRY_DATA> countryList;

public:
	CCountryAvailabilityDesc(void);
	~CCountryAvailabilityDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
