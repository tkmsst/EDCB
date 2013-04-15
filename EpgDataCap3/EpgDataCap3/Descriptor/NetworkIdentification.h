#pragma once

/*
8.2.8.3.2 ネットワーク識別記述子（Network_Identification_descriptor）
この記述子は、パーシャルトランスポートストリームが作り出された元のネットワーク
を明確にする為に用いられる。SIT の伝送情報記述ループにのみに挿入される。（表8-2-11
参照）

network_identification_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	country_code			24 bslbf
	media_type				16 bslbf
	network_id				16 uimsbf
	for(i=0; i<N; i++){
		private_data		8 bslbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
country_code（国コード）：この24 ビットのフィールドは、ISO3166 で規定されるアルファベッ
ト3 文字コードを使用して国名を表わす。この記述子に使用された場合は、パーシャルトランス
ポートストリームの生成された分配システムの国を表わす。各文字は、ISO8859-1 に従って8 ビ
ットで符号化され、その順で24 ビットフィールドに挿入される。日本の3 文字コードは「JPN」
であり、次のように符号化される。
「0100 1010 0101 0000 0100 1110」
media_type（メディア分類）：この16 ビットのフィールドは、アルファベット2 文字が挿入さ
れ、その2 文字によってメディアのタイプを表わす。この記述子に使用された場合は、パーシャ
ルトランスポートストリームの生成された分配システムのメディアタイプを表わす。各文字は、
ISO8859-1 に従って8 ビットで符号化され、その順で16 ビットフィールドに挿入される。メデ
ィアの種類は、下記による。
network_id（ネットワーク識別）：これは16 ビットのフィールドで、パーシャルトランスポート
ストリームの生成された分配システムのネットワーク識別の値が記述される。オリジナルの分配
システムでは、NIT にこの値が記述されており、そのフィールド値の割り当ては標準化機関の指
定による。
private_data（プライベートデータ）：これは8×N ビットのフィールドで、個別に定義された値
を持つ。
*/

#include "../../../Common/Util.h"

class CNetworkIdentification
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	CHAR country_code[4];
	WORD media_type;
	WORD network_id;
	BYTE private_dataLength;
	BYTE* private_data;
public:
	CNetworkIdentification(void);
	~CNetworkIdentification(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
