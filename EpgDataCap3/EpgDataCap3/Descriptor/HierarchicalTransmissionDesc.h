#pragma once

/*
6.2.22 階層伝送記述子 (Hierarchical transmission descriptor）
階層伝送記述子（表6－37 参照）は、番組内容を階層化して伝送する場合の、階層化し
たストリーム間の関係を示すのに用いられる。

hierarchical_transmission_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	reserved_future_use		7 bslbf
	quality_level			1 bslbf
	reserved_future_use		3 bslbf
	reference_PID			13 uimsbf
}

broadcasting_flag（放送／非放送種別）：これは2 ビットのフィールドで、表6－35 に従
って放送／非放送を示す。
broadcasting_identifier（放送の標準方式種別）：これは6 ビットのフィールドで、表6
－36 に従って放送の標準方式を示す。
quality_level（階層レベル）：階層化した段階を示す。階層構造は、HQ、LQ の2 段階と
し、階層レベルの値が1 の場合、そのストリームは高階層であることを示す。階層レベル
の値が0 の場合、そのストリームは低階層であることを示す。
reference_PID（参照先PID）：階層構造を持っているすべてのストリームについて、参照
先のエレメンタリーストリームのPID を示す。

*/

#include "../../../Common/Util.h"

class CHierarchicalTransmissionDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE quality_level;
	WORD reference_PID;
public:
	CHierarchicalTransmissionDesc(void);
	~CHierarchicalTransmissionDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
