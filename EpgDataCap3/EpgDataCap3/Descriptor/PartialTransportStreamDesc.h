#pragma once

/*
8.2.8.3.1 パーシャルトランスポートストリーム記述子
(Partial Transport Stream descriptor)
この記述子は、パーシャルトランスポートストリームを記録するために必要とされる情
報として用いられる。(表8-2-10 参照)

partial_transport_stream_descriptor(){
	descriptor_tag						8 uimsbf
	descriptor_length					8 uimsbf
	reserved_future_use					2 bslbf
	peak_rate							22 uimsbf
	reserved_future_use					2 bslbf
	minimum_overall_smoothing_rate		22 uimsbf
	reserved_future_use					2 bslbf
	maximum_overall_smoothing_buffer	14 uimsbf
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
peak_rate (ピークレート)：最大瞬時トランスポートパケットレート（すなわち、188 バ
イトを2 つの連続するトランスポートストリームパケットのスタート時間の時間間隔で除
算したものである）。このピークレートの上限が少なくとも規定されるべきである。この
22 ビットフィールドは400 ビット／秒単位の正の整数でコード化される。
minimum_overall_smoothing_rate (最小総スムージングレート)：全トランスポートス
トリームの最小総スムージングバッファのリークレート（すべてのパケットが含まれる）。
この22 ビットフィールドは400 ビット／秒単位の正の整数でコード化される。値
0x3FFFFF は最小スムージングレートが未定義であることを示すのに用いられる。
maximum_overall_smoothing_buffer (最大総スムージングバッファ)：全トランスポー
トストリームの最大スムージングバッファサイズ（すべてのパケットが含まれる）。この
14 ビットフィールドは1byte 単位の正の整数でコード化される。値0x3FFF は最大スム
ージングバッファサイズが未定義であることを示すのに用いられる。
*/

#include "../../../Common/Util.h"

class CPartialTransportStreamDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	DWORD peak_rate;
	DWORD minimum_overall_smoothing_rate;
	WORD maximum_overall_smoothing_buffer;
public:
	CPartialTransportStreamDesc(void);
	~CPartialTransportStreamDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
