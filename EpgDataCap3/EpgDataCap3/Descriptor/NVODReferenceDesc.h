#pragma once

/*
6.2.10 NVOD 基準サービス記述子（Near Video On Demand reference descriptor）
本記述子は、タイムシフトサービス記述子およびタイムシフトイベント記述子と共に、
放送開始時間以外はシーケンスが同じであるイベントを伝送している複数のサービスを効
率良く記述する手段を提供する。これらのタイムシフトサービスは、複数サービスから該
当サービスを選択することにより、ユーザーが任意の時刻に番組開始時間に近いサービス
を選択できることから、ニアビデオオンデマンド（NVOD）と呼ばれる。
NVOD 基準サービス記述子（表6－20 参照）は、NVOD サービスを構成するサービス
の一覧を示す。各々のサービスは、該当するSDT サブテーブルのタイムシフトサービス記
述子にも記述されている。（6.2.19 項参照）タイムシフトサービス記述子は、基準サービ
ス識別によりタイムシフトサービスを関連づけている。基準サービス識別は、全NVOD サ
ービスを記述するラベルであるが、それ自身はPMT 内のいずれのプログラム番号にも対
応しない。
タイムシフトイベント記述子は、各々のタイムシフトサービスのイベント情報に用いら
れる。各イベントに全情報を重複して記述しなくてよい代わりに、タイムシフトイベント
記述子は基準サービスの基準イベント識別を指し示す。全イベント情報は、基準サービス
のイベント情報に示される。
NVODサービスを構成するサービスは同一トランスポートストリーム内に存在する必要
はないが、NVOD サービスのサービスを伝送している全てのトランスポートストリームの
SI に基準サービスの記述が必須である。

NVOD_reference_descriptor(){
	descriptor_tag 8 uimsbf
	descriptor_length 8 uimsbf
	for (i=0;i<N;i++) {
		transport_stream_id 16 uimsbf
		original_network_id 16 uimsbf
		service_id 16 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
transport_stream_id（トランスポートストリーム識別）：これは16 ビットのフィールド
で、トランスポートストリームを識別する。
original_network_id（オリジナルネットワーク識別）：この16 ビットのフィールドは、
元の伝送システムのネットワーク識別を規定するラベルの役割をする。
service_id（サービス識別）：これは16 ビットのフィールドで、そのトランスポートスト
リーム内のサービスを識別する。サービス識別は、対応するプログラムマップセクション
内の放送番組番号識別（program_number）に等しい。
*/

#include "../../../Common/Util.h"

class CNVODReferenceDesc
{
public:
	typedef struct _SERVICE_DATA{
		WORD original_network_id;
		WORD transport_stream_id;
		WORD service_id;
	} SERVICE_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	vector<SERVICE_DATA> serviceList;

public:
	CNVODReferenceDesc(void);
	~CNVODReferenceDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
