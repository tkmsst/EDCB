#pragma once

/*
6.2.45 コンテント利用記述子 (Content availability descriptor)
コンテント利用記述子（表6-87 参照）は、記録や出力を制御する情報を示し、放送局（著
作権者側）が番組の記録や出力の制御を行う時に、デジタルコピー制御記述子と組み合わ
せて用いられる。

content_availability_descriptor () {
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	reserved_future_use		1 bslbf
	copy_restriction_mode	1 bslbf
	image_constraint_token	1 bslbf
	retention_mode			1 bslbf
	retention_state			3 bslbf
	encryption_mode			1 bslbf
	for(i=0;i<N;i++){
		reserved_future_use		8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
copy_restriction_mode（コピー制限モード）：この1 ビットのフィールドは、コピー個数
制限のモードを示し、事業者の運用規定によって定められる。
image_constraint_token（解像度制限ビット）：この1 ビットのフィールドは、映像信号
出力の画質制限の有無を示す。このフィールドが「0」の場合、映像信号出力の解像度を制
限しなければならない。「1」の場合、制限を行わなくてよい。
retention_mode（一時蓄積制御ビット）：この１ビットのフィールドが「０」の場合、デ
ジタルコピー制御記述子のdigital_recording_control_data が「コピー禁止」であっても一
時蓄積が可能であることを示す。「１」の場合、一時蓄積を行うことはできない。
retention_state（一時蓄積許容時間）：この３ビットのフィールドは、コンテンツを受信
してからの一時蓄積許容時間を表し、表6-88 にしたがって符号化される
encryption_mode（出力保護ビット）：この１ビットのフィールドは、高速デジタルイン
タフェース出力の出力保護の有無を示す。このフィールドが「０」の場合、高速デジタル
インタフェース出力においては、保護の処理を行わなければならない。「１」の場合、保
護を行わなくてよい。

*/

#include "../../../Common/Util.h"

class CContentAvailabilityDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE copy_restriction_mode;
	BYTE image_constraint_token;
	BYTE retention_mode;
	BYTE retention_state;
	BYTE encryption_mode;

public:
	CContentAvailabilityDesc(void);
	~CContentAvailabilityDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
