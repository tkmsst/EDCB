#pragma once

/*
6.2.12 パレンタルレート記述子（Parental rating descriptor）
この記述子（表6－22 参照）は、年齢に基づいた視聴制限を表し、また、他の制限条件
に基づくよう拡張することが可能である。

parental_rating_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	for (i=0;i<N;i++){
		country_code			24 bslbf
		rating					8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
country_code（国コード）：この24 ビットのフィールドは、ISO 3166-1(23)で規定される
アルファベット3 文字コードを使用して国名を表す。各文字は、ISO 8859-1(24)に従って8
ビットで符号化され、その順で24 ビットフィールドに挿入される。
例： 日本の3 文字コードは「JPN」であり、次のように符号化される。
「0100 1010 0101 0000 0100 1110」
rating（年齢制限レート）：これは８ビットのフィールドで、表6－23 に従って視聴者の
推奨最低年齢を表す。

*/

#include "../../../Common/Util.h"

class CParentalRatingDesc
{
public:
	typedef struct _RATING_DATA{
		CHAR country_code[4];
		BYTE rating;
	} RATING_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	vector<RATING_DATA> ratingList;

public:
	CParentalRatingDesc(void);
	~CParentalRatingDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
