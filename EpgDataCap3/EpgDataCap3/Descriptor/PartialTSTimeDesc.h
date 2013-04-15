#pragma once

/*
8.2.8.3.3 パーシャルトランスポートストリームタイム記述子
(partialTS_Time_descriptor)
event の時間情報、及び送出した時の時間情報を記述することができる。SIT に記述さ
れる。transmission_info_loop に記述する場合は、jst_time のみの記述とし、event の情
報は記述しない。Event の情報を記述する場合は、service_loop にdescriptor を挿入する。
SIT の中にこのdescriptor を複数挿入する事は好ましくない。（表8-2-12 参照）

partialTS_time_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	event_version_number	8 uimsbf
	event_start_time		40 bslbf
	duration				24 uimsbf
	offset					24 bslbf
	reserved				5 bslbf
	offset_flag				1 bslbf
	other_descriptor_status	1 bslbf
	jst_time_flag			1 bslbf
	if(jst_time_flag == 1){
		jst_time				40 bslbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
event_version_number (番組バージョン番号)：event のステータスの切れ目を識別する
ために使用。
切れ目で＋１とする。あるサービスを送信中、イベントが変わった時にカウントアップ
する。
event_start_time (番組開始時間)：event の開始時間を記述する。時間表示については、
EIT に記述されているstart_time と同じ。この時間情報を使用しない場合は、all 1 を記
述。
duration (継続時間)：event の継続時間を記述する。時間表示については、EIT に記述
されているduration と同じ。時間情報を記述しない場合は、all 1 を記述
Offset (オフセット時間)：オフセット時間。event_start_time またはjst_time がある時
は、その時間にアプライされる。0x000000 の時、オフセットはアプライされない。時間
の記述は、duration と同じ。
offset_flag (オフセットフラグ)：オフセット時間分進めるか遅らせるかを定義
0：event_start_time 及びjst_time にoffset の値を足した時間で運用。
1：event_start_time 及びjst_time にoffset の値を引いた時間で運用。
other_descriptor_status (他記述子ステータス)：SIT で使われるpartialTS_time_
descriptor 以外の状態を記述する。
1：他のdescriptor が変わっている可能性が有る。
0：他のdescriptor は変化していない。
jst_time_flag (jst 時間フラグ)：これが１となると、続くフィールドにjst_time が現れ
る事を示す。
jst_time (jst 時間)：現在の時刻情報。TDT に記述されるjst_time を誤差2 秒以内で記
述する。

*/

#include "../../../Common/Util.h"

class CPartialTSTimeDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE event_version_number;
	SYSTEMTIME event_start_time;
	WORD duration_HH;
	WORD duration_MM;
	WORD duration_SS;
	WORD offset_HH;
	WORD offset_MM;
	WORD offset_SS;
	BYTE offset_flag;
	BYTE other_descriptor_status;
	BYTE jst_time_flag;
	SYSTEMTIME jst_time;
public:
	CPartialTSTimeDesc(void);
	~CPartialTSTimeDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
