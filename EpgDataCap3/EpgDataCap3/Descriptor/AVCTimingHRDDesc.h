#pragma once

/*
6.2.48 AVC タイミングHRD 記述子(AVC timing and HRD descriptor)
AVC タイミングHRD 記述子（表6-91 参照）は、ITU-T 勧告H.264|ISO/IEC 14496-10
の映像ストリームの時間情報とHRD（Hypothetical Reference Decoder: 仮想参照デコー
ダ）の情報を記述するために用いられる。AVC 映像ストリームがVUI（Video Usability
Information: 映像有用情報）パラメータを伝送しない場合、本記述子をPMT に記述する
必要がある。詳細はITU-T 勧告H.222.0|ISO/IEC 13818-1(21)を参照のこと。

AVC_timing_and_HRD_descriptor () {
	descriptor_tag						8 uimsbf
	descriptor_length					8 uimsbf
	hrd_management_valid_flag			1 bslbf
	reserved							6 bslbf
	picture_and_timing_info_present		1 bslbf
	if(picture_and_timing_info_present = = 1){
		90kHz_flag							1 bslbf
		reserved							7 bslbf
		if(90kHz_flag = = 0){
			N									32 uimsbf
			K									32 uimsbf
		}
		num_units_in_tick					32 uimsbf
	}
	fixed_frame_rate_flag				1 bslbf
	temporal_poc_flag					1 bslbf
	picture_to_display_conversion_flag	1 bslbf
	reserved							5 bslbf
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
hrd_management_valid_flag（HRD 管理有効フラグ）：この１ビットのフィールドが「1」
の場合、ITU-T 勧告H.264|ISO/IEC 14496-10 付録C に定義されているBuffering Period
SEI がAVC 映像ストリームに含まれている必要があり、NAL HRD（Network Abstraction
Layer Hypothetical Reference Decoder：ネットワーク抽象層仮想参照デコーダ）のCPB
（Coded Picture Buffer：符号化画像バッファ）への転送スケジュールに従って、MBn か
らEBn へバイトが転送されることを示す。このフィールドが「0」の場合、ITU-T 勧告
H.222.0|ISO/IEC 13818-1 の 2.14.3.1 節で定義されるリークメソッドがMBn からEBn へ
の転送に用いられる。
picture_and_timing_info_present（時間情報有効フラグ）：このフィールドが「1」の場
合、90kHz_flag とシステムクロックへの正確なマッピングのためのパラメータを本記述子
が含んでいることを示す。
90kHz_flag（90kHz フラグ）：このフィールドが「1」の場合、AVC タイムベースが90kHz
であることを示す。AVC タイムベースの周期は、ITU-T 勧告H.264|ISO/IEC 14496-10
付録E で定義されたAVC のtime_scale で定義される。
N, K：AVC のtime_scale とsystem_clock_reference の間の関係を次式で定義するパラメ
ータであり、K はN 以上である。
time_scale = (N * system_clock_frequency) / K
num_units_in_tick（時間計算の単位）：ITU-T 勧告H.264|ISO/IEC 14496-10 の付録E
を参照のこと。
fixed_frame_rate_flag（固定フレームレートフラグ）：ITU-T 勧告H.264|ISO/IEC
14496-10 の付録E を参照のこと。このフラグが「1」の場合、符号化フレームレートはAVC
映像エレメンタリーストリーム内で一定であることを表す。このフラグが「0」の場合、
AVC 映像ストリームのフレームレートに関する情報が本記述子にはないことを表す。
temporal_poc_flag（時間POC フラグ）：このフィールドが「1」でfixed_frame_rate_flag
が「1」の場合、AVC 映像ストリームはPOC（Picture Order Count：画像順番）情報を
伝送しなければならない。ITU-T 勧告H.264|ISO/IEC 14496-10 の付録E を参照のこと。
このフィールドが「0」の場合、AVC 映像ストリームのPOC 情報と時間との関係に関する
情報は伝送されない。
picture_to_display_conversion_flag（映像表示変換フラグ）：このフィールドが「1」の場
合、AVC 映像ストリームが符号化映像の表示のための情報を伝送していることを示す。こ
のフィールドが「0 」の場合、AVC 映像ストリームのVUI パラメータの
pic_struct_present_flag は「0」としなければならない。

*/

#include "../../../Common/Util.h"

class CAVCTimingHRDDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE hrd_management_valid_flag;
	BYTE picture_and_timing_info_present;
	BYTE _90kHz_flag;
	DWORD N;
	DWORD K;
	DWORD num_units_in_tick;
	BYTE fixed_frame_rate_flag;
	BYTE temporal_poc_flag;
	BYTE picture_to_display_conversion_flag;

public:
	CAVCTimingHRDDesc(void);
	~CAVCTimingHRDDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
