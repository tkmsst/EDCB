#pragma once

/*
6.2.44 ロゴ伝送記述子（Logo transmission descriptor）
ロゴ伝送記述子は、簡易ロゴ用文字列、CDT 形式のロゴへのポインティングなどを記述するた
めに使用する。表6-85 参照。

logo_transmission_descriptor(){
	descriptor_tag				8 uimsbf
	descriptor_length			8 uimsbf
	logo_transmission_type		8 uimsbf
	if(logo_transmission_type == 0x01){
		reserved_future_use			7 bslbf
		logo_id						9 uimsbf
		reserved_future_use			4 bslbf
		logo_version				12 uimsbf
		download_data_id			16 uimsbf
	}else if(logo_transmission_type == 0x02){
		reserved_future_use			7 bslbf
		logo_id						9 uimsbf
	}else if(logo_transmission_type == 0x03){
		for(i=0;i<N;i++){
			logo_char				8 uimsbf
		}
	}else
		for(j=0;j<M;j++){
			reserved_future_use		8 bslbf
		}
	｝
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
logo_transmission_type（ロゴ伝送種別）：この8 ビットのフィールドは、表6-86 に示す
ロゴの伝送方式を表す（ARIB STD-B21 参照）。
logo_id（ロゴ識別）：この9 ビットは当該サービスに定義するロゴデータのＩＤ値を記載
する（ARIB STD-B21 参照）。
download_data_id（ダウンロードデータ識別）：この16 ビットはダウンロードされるデ
ータの識別を表す。ロゴデータが配置されているCDT のtable_id_extension の値と一致
する（ARIB STD-B21 参照）。
logo_version（ロゴバージョン番号）：この12 ビットは当該logo_id のバージョン番号を
記載する（ARIB STD-B21 参照）。
logo_char（簡易ロゴ用文字列）：この8 ビットは簡易ロゴ用の8 単位符号文字列を記載す
る。

*/

#include "../../../Common/Util.h"

class CLogoTransmissionDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE logo_transmission_type;
	WORD logo_id;
	WORD logo_version;
	WORD download_data_id;
	BYTE logo_charLength;
	CHAR* logo_char;
public:
	CLogoTransmissionDesc(void);
	~CLogoTransmissionDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
