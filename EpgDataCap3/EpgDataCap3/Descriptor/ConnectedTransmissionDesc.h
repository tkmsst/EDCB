#pragma once

/*
6.2.41 連結送信記述子（Connected transmission descriptor）
連結送信記述子は、地上音声伝送路において連結送信時の物理的条件を示す。表6-79 参
照。

connected_transmission_descriptor (){
	descriptor_tag						8 uimsbf
	descriptor_length					8 uimsbf
	connected_transmission_group_id		16 uimsbf
	segment_type						2 bslbf
	modulation_type_A					2 bslbf
	modulation_type_B					2 bslbf
	reserved_future_use					2 bslbf
	for(i= 0;i<N;i++){
		additional_connected_transmission_info		8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
connected_transmission_group_id（連結送信グループ識別）：この16 ビットのフィール
ドは、連結送信グループを識別するラベルの役割をする。
segment _type（セグメント形式種別）：これは2 ビットのフィールドで、表6-80 に従っ
てセグメント形式の種別を示す。
modulation_type_A（変調方式種別A）：これは2 ビットのフィールドで、表6-81 に従っ
てA 階層の変調方式の種別を示す。
modulation_type_B（変調方式種別B）：これは2 ビットのフィールドで、表6-81 に従っ
てB 階層の変調方式の種別を示す。セグメント形式種別が1 セグメントの場合は、意味を
持たない。
additional_connected_transmission_info（付加識別情報）：これは 8 ビットのフィール
ドで、事業者の運用規定で定める補足情報の格納に利用される。

*/

#include "../../../Common/Util.h"

class CConnectedTransmissionDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD connected_transmission_group_id;
	BYTE segment_type;
	BYTE modulation_type_A;
	BYTE modulation_type_B;
	BYTE additional_connected_transmission_infoLength;
	BYTE* additional_connected_transmission_info;
public:
	CConnectedTransmissionDesc(void);
	~CConnectedTransmissionDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
