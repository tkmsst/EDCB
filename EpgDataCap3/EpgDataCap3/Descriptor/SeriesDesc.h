#pragma once

/*
6.2.33 シリーズ記述子（Series descriptor）
シリーズ記述子は、シリーズ番組を識別するために用いる。表6－65 参照。

series_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	series_id				16 uimsbf
	repeat_label			4 uimsbf
	program_pattern			3 uimsbf
	expire_date_valid_flag	1 uimsbf
	expire_date				16 uimsbf
	episode_number			12 uimsbf
	last_episode_number		12 uimsbf
	for(i=0; i<N; i++){
		series_name_char		8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
series_id（シリーズ識別）：これは16 ビットのフィールドで、シリーズをユニークに識別
するための識別子である。
repeat_label（再放送ラベル）：この4 ビットのフィールドは、シリーズの放送期間とシ
リーズの再放送の放送期間が重なる場合に、編成を区別するラベルとして用いる。オリジ
ナルのシリーズの放送には「0x0」を与える。
program_pattern（編成パターン）：この3 ビットのフィールドは、表6－66 に従い、シ
リーズ番組の編成のパターンを表す。これによりシリーズに属するイベントが次にいつ現
れるかの目安がわかる。
expire_date_valid_flag（有効期限フラグ）：この1 ビットのフラグは、次に続くexpire_date
の値が有効であることを示す。シリーズの終了予定日の値が有効な場合、この値を「1」と
する。
expire_date（有効期限）：この16 ビットのフィールドは、シリーズが有効な期限の年月
日をMJD の下位16 ビットで表す。何らかの原因で最終回のイベントを認識できなかった
場合も、この日付を過ぎると受信機はシリーズが終了したと認識する。
episode_number（話数）：この12 ビットのフィールドは、この記述子が示す番組の、シ
リーズ内の話数を示す。第1 回から第4095 回まで記載できる。話数がこれを超える場合
はシリーズを別に定義する。
連続番組の場合で番組回数が定義できない場合は、「0x000」とする。
last_episode_number（番組総数）：この12 ビットのフィールドは、当該シリーズ番組の
番組総数を示す。第1 回から第4095 回まで記載できる。番組総数がこれを超える場合は、
シリーズを別に定義する。
最終回が未定の場合、「0x000」とする。
series_name_char（シリーズ名）：この文字符号フィールドでは、シリーズ名が伝送され
る。文字情報の符号化については、付録A 参照。

*/

#include "../../../Common/Util.h"

class CSeriesDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD series_id;
	BYTE repeat_label;
	BYTE program_pattern;
	BYTE expire_date_valid_flag;
	WORD expire_date;
	WORD episode_number;
	WORD last_episode_number;
	BYTE series_name_charLength;
	CHAR* series_name_char;
public:
	CSeriesDesc(void);
	~CSeriesDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
