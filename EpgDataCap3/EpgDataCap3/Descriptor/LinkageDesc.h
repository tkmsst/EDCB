#pragma once

/*
6.2.8 リンク記述子（Linkage descriptor）
リンク記述子（表6－13 参照）は、SI システムに記載されているある特定のものに関連
した追加情報を視聴者が要求した場合に提供されるサービスを識別する。データ構造内に
おけるリンク記述子の位置で追加情報が利用可能なものを示す。たとえば、NIT 内のリン
ク記述子はネットワークについての追加情報を提供するサービスを指し、BAT 内では、ブ
ーケ等についてのサービス情報にリンクする。
CA 代替サービスは、リンク記述子を使用することでも識別できる。CA がSI システム
に記載されている特定のものへのアクセスを拒否した場合には、この代替サービスが受信
機によって自動的に選択される。

linkage_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	transport_stream_id		16 uimsbf
	original_network_id		16 uimsbf
	service_id				16 bslbf
	linkage_type			8 uimsbf
	for (i=0;i<N;i++){
		private_data_byte		8 bslbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
transport_stream_id（トランスポートストリーム識別）：これは16 ビットのフィールド
で、指示されている情報サービスが含まれるトランスポートストリームを識別する。
original_network_id（オリジナルネットワーク識別）：この16 ビットのフィールドは、
指示されている情報サービスの元の分配システムのネットワーク識別を規定するラベルの
役割をする。
service_id（サービス識別）：これは16 ビットのフィールドで、そのトランスポートスト
リーム内の情報サービスをユニークに識別する。サービス識別は、対応するプログラムマ
ップセクション内の放送番組番号識別（program_number）に等しい。リンク種別の値が
0x04 の場合、サービス識別のフィールドは意味を持たず、0x0000 に設定される。
linkage_type（リンク種別）：これは8 ビットのフィールドで、リンクの種別などの情報
を示す。（表6－14 参照）
private_data_byte（プライベートデータ）：これは8 ビットのフィールドで、個別に定義
された値を持つ
*/

#include "../../../Common/Util.h"

class CLinkageDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD transport_stream_id;
	WORD original_network_id;
	WORD service_id;
	WORD linkage_type;
	BYTE private_data_byteLength;
	BYTE* private_data_byte;
public:
	CLinkageDesc(void);
	~CLinkageDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
