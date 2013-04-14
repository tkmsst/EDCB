#pragma once

/*
6.2.47 AVC ビデオ記述子(AVC video descriptor)
AVC ビデオ記述子（表6-90 参照）は、ITU-T 勧告H.264|ISO/IEC 14496-10 の映像ス
トリーム（AVC ストリーム）の基本的な符号化パラメータを記述するために用いられる。
本記述子がPMT に記述されない場合、AVC ストリームはAVC 静止画像やAVC 24 時間
映像を含んではならない。詳細はITU-T 勧告H.222.0|ISO/IEC 13818-1(21)を参照のこと。

AVC_video_descriptor () {
	descriptor_tag				8 uimsbf
	descriptor_length			8 uimsbf
	profile_idc					8 uimsbf
	constraint_set0_flag		1 bslbf
	constraint_set1_flag		1 bslbf
	constraint_set2_flag		1 bslbf
	AVC_compatible_flags		5 bslbf
	level_idc					8 uimsbf
	AVC_still_present			1 bslbf
	AVC_24_hour_picture_flag	1 bslbf
	reserved					6 bslbf
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
profile_idc（AVC プロファイル）：AVC 映像ストリームのプロファイルを示す。ITU-T
勧告H.264|ISO/IEC 14496-10 の7.4.2.1 節を参照のこと。
constraint_set0_flag（セット0 制限フラグ）：ITU-T 勧告H.264|ISO/IEC 14496-10 の
7.4.2.1 節を参照のこと。
constraint_set1_flag（セット1 制限フラグ）：ITU-T 勧告H.264|ISO/IEC 14496-10 の
7.4.2.1 節を参照のこと。
constraint_set2_flag（セット2 制限フラグ）：ITU-T 勧告H.264|ISO/IEC 14496-10 の
7.4.2.1 節を参照のこと。
AVC_compatible_flags（AVC 互換性フラグ）：ITU-T 勧告H.264|ISO/IEC 14496-10 で
規定されるシーケンスパラメータセットのreserved_zero_5bits と同じ値である。
level_idc（AVCレベル）：AVC映像ストリームのレベルを示す。ITU-T 勧告H.264|ISO/IEC
14496-10 の7.4.2.1 節を参照のこと。
AVC_still_present（AVC 静止画像あり）：このフィールドが「1」の場合、AVC 映像ス
トリームにAVC 静止画が含まれる。このフィールドが「0」の場合、AVC 映像ストリーム
はAVC 静止画を含んではならない。
AVC_24_hour_picture_flag（AVC 24 時間映像フラグ）：このフィールドが「1」の場合、
AVC 映像ストリームにAVC 24 時間映像が含まれる。AVC 24 時間映像とは、24 時間を越
える提示時間を有するAVC アクセスユニットである。このフィールドが「0」の場合、AVC
映像ストリームはAVC 24 時間映像を含んではならない。

*/

#include "../../../Common/Util.h"

class CAVCVideoDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE profile_idc;
	BYTE constraint_set0_flag;
	BYTE constraint_set1_flag;
	BYTE constraint_set2_flag;
	BYTE AVC_compatible_flags;
	BYTE level_idc;
	BYTE AVC_still_present;
	BYTE AVC_24_hour_picture_flag;
public:
	CAVCVideoDesc(void);
	~CAVCVideoDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
