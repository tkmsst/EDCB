#pragma once

/*
6.2.25 ローカル時間オフセット記述子（Local time offset descriptor）
ローカル時間オフセット記述子（表6－41 参照）は、サマータイム実施時に実際の時刻
（UTC+9 時間）と人間系への表示時刻に一定のオフセット値を持たせるときに用いる。

local_time_offset_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	for(i=0;i<N;i++){
		country_code				24 bslbf
		country_region_id			6 bslbf
		reserved					1 bslbf
		local_time_offset_polarity	1 bslbf
		local_time_offset			16 bslbf
		time_of_change				40 bslbf
		next_time_offset			16 bslbf
	}
}

broadcasting_flag（放送／非放送種別）：これは2 ビットのフィールドで、表6－35 に従
って放送／非放送を示す。
broadcasting_identifier（放送の標準方式種別）：これは6 ビットのフィールドで、表6
－36 に従って放送の標準方式を示す。
country_code（国コード）：この24 ビットのフィールドは、ISO 3166-1(23)で規定される
アルファベット3 文字コードを使用して国名を表す。各文字は、ISO 8859-1(24)に従って8
ビットで符号化され、その順で24 ビットフィールドに挿入される。
例： 日本の3 文字コードは「JPN」であり、次のように符号化される。
「0100 1010 0101 0000 0100 1110」
country_region_id（国地域識別）：この6 ビットのフィールドは、国内の地域（ゾーン）
を指定するためのものである。地域を区別しない場合は「000000」を使用する。
local_time_offset_polarity（ローカル時間オフセット極性）：この１ビットの情報は、以
下に続くローカル時間オフセット値および変更後時間オフセット値の極性を指定する。こ
のビットが ”0” のときは、JST_time に対してオフセット時間分進めることを意味し、”1”
のときは、JST_time に対してオフセット時間分遅らせることを意味する。
local_time_offset（ローカル時間オフセット）：この16 ビットのフィールドは、JST_time
に対する、現在のオフセット時間を -12 時間から+12 時間の範囲で指定する。この16 ビ
ットは、オフセット時間の10 時間の位、1 時間の位、10 分の位、1 分の位の4 個を、それ
ぞれ4 ビット2 進化10 進数（BCD）で符号化する。
time_of_change（変更時刻）：この40 ビットのフィールドは、日本標準時（UTC+9 時間）
と修正ユリウス日（MJD）（付録C 参照）によって表現する、次の異なるオフセット時間
へ変更される日付と時刻を含む。このフィールドは、MJD の下位16 ビットを16 ビットで
符号化し、続く24 ビットを6 個の4 ビット2 進化10 進数（BCD）で符号化する。
next_time_offset（変更後時間オフセット）：この16 ビットのフィールドは、time_of_change
に指定された日時以降のオフセット時間を -12 時間から+12 時間の範囲で指定する。この
16 ビットは、オフセット時間の10 時間の位、1 時間の位、10 分の位、1 分の位の4 個を、
それぞれ4 ビット2 進化10 進数（BCD）で符号化する。

*/

#include "../../../Common/Util.h"

class CLocalTimeOffsetDesc
{
public:
	typedef struct _LOCAL_TIME_OFFSET_DATA{
		CHAR country_code[4];
		BYTE country_region_id;
		BYTE local_time_offset_polarity;
		WORD local_time_offset; //分単位
		SYSTEMTIME time_of_change;
		WORD next_time_offset;	//分単位
	} LOCAL_TIME_OFFSET_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	vector<LOCAL_TIME_OFFSET_DATA> timeOffsetList;

public:
	CLocalTimeOffsetDesc(void);
	~CLocalTimeOffsetDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
