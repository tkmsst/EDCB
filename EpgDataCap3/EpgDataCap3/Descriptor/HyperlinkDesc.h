#pragma once

/*
6.2.29 ハイパーリンク記述子（Hyperlink descriptor）
ハイパーリンク記述子（表6－49 参照）は、他の番組や番組内部、番組関連情報に対す
るリンクを記述するために使用される。

hyperlink_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	hyper_linkage_type		8 uimsbf
	link_destination_type	8 uimsbf
	selector_length			8 uimsbf
	for(i=0; i<selector_length; i++){
		selector_byte			8 uimsbf
	}
	for(i=0; i<N; i++){
		private_data			8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
hyper_linkage_type（ハイパーリンク種別）：この8 ビットのフィールドはリンクの形態
を示し、表6－50 に従って符号化される。
link_destination_type（リンク先種別）：この８ビットのフィールドはリンク先の種別を
表わし、表6－51 に従って符号化される。
selector_length（セレクタ長）：この8 ビットのフィールドは、後続のセレクタ領域のバ
イト長を表す。
selector_byte（セレクタバイト）：これは8 ビットのフィールドである。一連のセレクタ
領域は、リンク先種別毎に規定される以下の形式によってリンク先を記述する。


表6－52 セレクタ領域の記述（link_destination_type:0x01）
link_service_info(){
	original_network_id		16 uimsbf
	transport_stream_id		16 uimsbf
	service_id				16 uimsbf
}

original_network_id（オリジナルネットワーク識別）：これは16 ビットのフィールドで、
リンク先のサービスが属する元の分配システムのネットワーク識別を表すラベルを記述す
る。
transport_stream_id（トランスポートストリーム識別）：これは16 ビットのフィールド
で、リンク先のサービスが属するトランスポートストリームを識別するラベルを記述する。
service_id（サービス識別）：これは16 ビットのフィールドで、リンク先のトランスポー
トストリーム内のサービスを識別するためのラベルで、対応するプログラムマップセクシ
ョン内の放送番組番号識別と同じ値を記述する。

表6－53 セレクタ領域の記述（link_destination_type:0x02）
link_event_info(){
	original_network_id		16 uimsbf
	transport_stream_id		16 uimsbf
	service_id				16 uimsbf
	event_id				16 uimsbf
}
original_network_id（オリジナルネットワーク識別）：これは16 ビットのフィールドで、
リンク先のイベントが属する元の分配システムのネットワーク識別を表すラベルを記述す
る。
transport_stream_id（トランスポートストリーム識別）：これは16 ビットのフィールド
で、リンク先のイベントが属するトランスポートストリームを識別するラベルを記述する。
service_id（サービス識別）：これは16 ビットのフィールドで、リンク先のイベントが属
するトランスポートストリーム内のサービスを識別するためのラベルで、対応するプログ
ラムマップセクション内の放送番組番号識別と同じ値を記述する。
event_id（イベント識別）：これは16 ビットのフィールドで、リンク先のイベントの識別
番号を記述する。

表6－54 セレクタ領域の記述（LINK_DESTINATION_TYPE:0X03）
link_module_info(){
	original_network_id		16 uimsbf
	transport_stream_id		16 uimsbf
	service_id				16 uimsbf
	event_id				16 uimsbf
	component_tag			8 uimsbf
	moduleId				16 uimsbf
}
original_network_id（オリジナルネットワーク識別）：これは16 ビットのフィールドで、
リンク先のカルーセルモジュールが属する元の分配システムのネットワーク識別を表すラ
ベルを記述する。
transport_stream_id（トランスポートストリーム識別）：これは16 ビットのフィールド
で、リンク先のカルーセルモジュールが属するトランスポートストリームを識別するラベ
ルを記述する。
service_id（サービス識別）：これは16 ビットのフィールドで、リンク先のカルーセルモ
ジュールが属するトランスポートストリーム内のサービスを識別するためのラベルで、対
応するプログラムマップセクション内の放送番組番号識別と同じ値を記述する。
event_id（イベント識別）：これは16 ビットのフィールドで、リンク先のカルーセルモジ
ュールが属するイベントの識別番号を記述する。
component_tag（コンポーネントタグ）：これは8 ビットのフィールドで、リンク先のカ
ルーセルモジュールを伝送するコンポーネントストリームを識別するラベルを記述する。
moduleId（モジュール識別）：これは16 ビットのフィールドで、リンク先のカルーセル
モジュールの識別番号を記述する。

表6－55 セレクタ領域の記述（link_destination_type:0x04）
link_content_info(){
	original_network_id		16 uimsbf
	transport_stream_id		16 uimsbf
	service_id				16 uimsbf
	content_id				32 uimsbf
}
original_network_id（オリジナルネットワーク識別）：これは16 ビットのフィールドで、
リンク先のコンテンツのモジュールが属する元の分配システムのネットワーク識別を表す
ラベルを記述する。
transport_stream_id（トランスポートストリーム識別）：これは16 ビットのフィールド
で、リンク先のコンテンツが属するトランスポートストリームを識別するラベルを記述す
る。
service_id（サービス識別）：これは16 ビットのフィールドで、リンク先のコンテンツが
属するトランスポートストリーム内のサービスを識別するためのラベルで、対応するプロ
グラムマップセクション内の放送番組番号識別と同じ値を記述する。
content_id（コンテンツ識別）：これは32 ビットのフィールドで、リンク先のコンテンツ
をサービス内で一意に識別する識別番号を記述する。

表6－56 セレクタ領域の記述（link_destination_type:0x05）
link_content_module_info(){
	original_network_id		16 uimsbf
	transport_stream_id		16 uimsbf
	service_id				16 uimsbf
	content_id				32 uimsbf
	component_tag			8 uimsbf
	moduleId				16 uimsbf
}
original_network_id（オリジナルネットワーク識別）：これは16 ビットのフィールドで、
リンク先のコンテンツのモジュールが属する元の分配システムのネットワーク識別を表す
ラベルを記述する。
transport_stream_id（トランスポートストリーム識別）：これは16 ビットのフィールド
で、リンク先のコンテンツのモジュールが属するトランスポートストリームを識別するラ
ベルを記述する。
service_id（サービス識別）：これは16 ビットのフィールドで、リンク先のコンテンツの
モジュールが属するトランスポートストリーム内のサービスを識別するためのラベルで、
対応するプログラムマップセクション内の放送番組番号識別と同じ値を記述する。
content_id（コンテンツ識別）：これは32 ビットのフィールドで、リンク先のモジュール
が属するコンテンツをサービス内で一意に識別する識別番号を記述する。
component_tag（コンポーネントタグ）：これは8 ビットのフィールドで、リンク先のカ
ルーセルモジュールを伝送するコンポーネントストリームを識別するラベルを記述する。
moduleId（モジュール識別）：これは16 ビットのフィールドで、リンク先のモジュール
の識別番号を記述する。

表6－57 セレクタ領域の記述（link_destination_type:0x06）
link_ert_node_info(){
	information_provider_id		16 uimsbf
	event_relation_id			16 uimsbf
	node_id						16 uimsbf
}
information_provider_id（情報提供者識別）：この16ビットのフィールドは、リンク先の
ノードが属するイベント関係サブテーブルの情報提供者識別を指定する。
event_relation_id（イベント関係識別）：この16 ビットのフィールドは、リンク先の属す
るイベント関係サブテーブルのイベント関係識別を指定する。
node_id（ノード識別）：この16 ビットのフィールドは、リンク先のノードのノード識別
を指定する。

表6－58 セレクタ領域の記述（link_destination_type:0x07）
link_stored_content_info(){
	for(i=0; i<N; i++){
		uri_char 8 uimsbf
	}
}
uri_char（URI 文字）：一連のフィールドは、蓄積されたデータサービスのコンテンツの
URI を記述する。URI の記述方法についてはARIB STD-B24 第二編9 章の規定による。

*/

#include "../../../Common/Util.h"

class CHyperlinkDesc
{
public:
	typedef struct _SELECTOR_DATA{
		WORD original_network_id;
		WORD transport_stream_id;
		WORD service_id;
		WORD event_id;
		BYTE component_tag;
		WORD moduleId;
		DWORD content_id;
		WORD information_provider_id;
		WORD event_relation_id;
		WORD node_id;
		CHAR uri_char[256];
	} SELECTOR_DATA;
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE hyper_linkage_type;
	BYTE link_destination_type;
	BYTE selector_length;
	vector<SELECTOR_DATA*> selectorList;
	BYTE private_dataLength;
	BYTE* private_data;
public:
	CHyperlinkDesc(void);
	~CHyperlinkDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );

protected:
	void Clear();
};
