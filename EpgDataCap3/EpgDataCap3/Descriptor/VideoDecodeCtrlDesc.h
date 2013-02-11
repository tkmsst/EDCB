#pragma once

/*
6.2.30 ビデオデコードコントロール記述子（Video decode control descriptor）
ビデオデコードコントロール記述子（表6-59 参照）は、小さい伝送速度で送信される
MPEG-I ピクチャで構成される静止画像を受信するため、及び映像フォーマットの切り替
わる点においてスムーズな表示をするために、ビデオデコードをコントロールする場合に
使用される。

video_decode_control_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	still_picture_flag		1 bslbf
	sequence_end_code_flag	1 bslbf
	video_encode_format		4 bslbf
	reserved_future_use		2 bslbf
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
still_picture_flag（静止画フラグ）：これは１ビットのフィールドで、「１」の場合は、
このコンポーネントが静止画（MPEG-I ピクチャ）であることを示す。「0」の場合は、こ
のコンポーネントが動画であることを示す。
sequence_end_code_flag（シーケンスエンドコードフラグ）：これは1 ビットのフィールド
で、このコンポーネントがビデオエンコードフォーマットで示される映像フォーマットの終
了点において、シーケンスエンドコード（MPEG-2 Video 規格の場合。MPEG-4 AVC 規格
の場合はエンド・ オブ・シーケンスNAL ユニット。以下同様。）を送信するストリームで
あるか否かを示す。「1」の場合は、その映像ストリームはシーケンスエンドコードが送信
されるストリームであることを示し、「0」の場合は、シーケンスエンドコードが送信され
ないストリームであることを示す。
video_encode_format（ビデオエンコードフォーマット）：これは4 ビットのフィールドで、
表6－60 に従ってこのコンポーネントのエンコードフォーマットを示す。

*/

#include "../../../Common/Util.h"

class CVideoDecodeCtrlDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE still_picture_flag;
	BYTE sequence_end_code_flag;
	BYTE video_encode_format;
public:
	CVideoDecodeCtrlDesc(void);
	~CVideoDecodeCtrlDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
