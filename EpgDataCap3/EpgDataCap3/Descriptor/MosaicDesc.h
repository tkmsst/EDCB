#pragma once

/*
6.2.9 モザイク記述子（Mosaic descriptor）
モザイクコンポーネントは、複数の異なる映像が集まり、1 つの符号化された映像コン
ポーネントとなったものである。個々の情報が画面上を小分割した位置に提示される様に
情報が編成されている。
モザイク記述子により、デジタル映像コンポーネントは要素セル内に区分けされ、要素
セルは論理セルに割り当てられ、論理セルに割り当てられた映像と実際の情報（例：ブー
ケ、サービス、イベント等）が関連づけられる。表6－15 参照。

mosaic_descriptor(){
	descriptor_tag							8 uimsbf
	descriptor_length						8 uimsbf
	mosaic_entry_point						1 bslbf
	number_of_horizontal_elementary_cells	3 uimsbf
	reserved_future_use						1 bslbf
	number_of_vertical_elementary_cells		3 uimsbf
	for (i=0,i<N; i++) {
		logical_cell_id							6 uimsbf
		reserved_future_use						7 bslbf
		logical_cell_presentation_info			3 uimsbf
		elementary_cell_field_length			8 uimsbf
		for (j=0,j<elementary_cell_field_length;j++) {
			reserved_future_use						2 bslbf
			elementary_cell_id						6 uimsbf
		}
		cell_linkage_info						8 uimsbf
		if (cell_linkage_info ==0x01){
			bouquet_id								16 uimsbf
		}
		if (cell_linkage_info ==0x02){
			original_network_id						16 uimsbf
			transport_stream_id						16 uimsbf
			service_id								16 uimsbf
		}
		if (cell_linkage_info ==0x03){
			original_network_id						16 uimsbf
			transport_stream_id						16 uimsbf
			service_id								16 uimsbf
		}
		if (cell_linkage_info ==0x04){
			original_network_id						16 uimsbf
			transport_stream_id						16 uimsbf
			service_id								16 uimsbf
			event_id								16 uimsbf
		}
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
mosaic_entry_point（最上位モザイク）：これは1 ビットのフィールドで、「1」に設定さ
れている場合、そのモザイクが最上位の階層のモザイクであることを示す。モザイクシス
テムはツリー構造を構成することが可能であり、このフラグはツリー構造の出発点である
ことを示す。
number_of_horizontal_elementary_cells（水平セル数）：この3 ビットのフィールドは、
表6－16 に従って、画面上の水平セル数を表わす。
number_of_vertical_elementary_cells（垂直セル数）：この3 ビットのフィールドは、画
面上の垂直セル数を表わす。符号は表6－17 を参照。
logical_cell_id（論理セル識別）：この6 ビットのフィールドは2 進形式で符号化される。
隣接する異なる要素セル（図6－1 参照）は、グループ化され論理セルを構成することが
可能である。論理セル番号はこのようにグループ化された要素セル番号に関係づけられる。
論理セル数の合計は、要素セル数（最大64）を超えることはできない。各々の要素セルは
１つの論理セルに割り当てられる。1 つの論理セルは1 つ以上の要素セルから構成される。
logical_cell_presentation_info（論理セル提示情報）：この3 ビットのフィールドは、論理
セルの提示種別を表わす。論理セル提示情報は、表6－18 に定義する提示形式を示す。
elementary_cell_field_length（要素セル情報長）：要素セル情報長は8 ビットのフィール
ドで、このフィールドの直後からこの論理セル識別のループ内の最後の要素セル識別まで
のバイト長を示す。
elementary_cell_id（要素セル識別）：この6 ビットのフィールドはセル番号を2 進数で
表す。このフィールドは0 からN の範囲の値をとる。
［注2］：要素セル番号は0 からN まで抜けなく付与される。0 は1 マス目（左上）のセ
ルに割り当てられる。番号は左から右、上から下の順に割り振られ、N 番は最下行の最後
（右下）のマスに割り振られる。
cell_linkage_info（セルリンク情報）：この8 ビットのフィールドは、表6－19 に従って、
論理セルで伝送される情報の種別を表す。
bouquet_id（ブーケ識別）：これは16 ビットのフィールドで、セルに記載されているブー
ケを識別する。
original_network_id（オリジナルネットワーク識別）：この16 ビットのフィールドは、
後続のフィールドとともに、サービス、イベントあるいはモザイクを独自に識別するラベ
ルの役割をする。（5.2 項参照）
transport_stream_id（トランスポートストリーム識別）：これは16 ビットのフィールド
で、セルに記載されているサービス、イベントあるいはモザイクが含まれるトランスポー
トストリームを識別する。
service_id（サービス識別）：これは16 ビットのフィールドで、そのトランスポートスト
リーム内のサービスを識別する。サービス識別は、対応するプログラムマップセクション
内の放送番組番号識別（program_number）に等しい。
このフィールドの解釈は、セルリンク情報の値によって以下のとおりとなる：
セルリンク情報＝「0x02」の場合、セルに記載されたサービスのサービス識別である。
セルリンク情報＝「0x03」の場合、セルに記載されたモザイクサービスのサービス識
別である。
セルリンク情報＝「0x04」の場合、セルに記載されたイベントのサービス識別である。
event_id（イベント識別）：これは16 ビットのフィールドで、記載されたイベントの番号
を示す。

*/

#include "../../../Common/Util.h"

class CMosaicDesc
{
public:
	typedef struct _CELL_DATA{
		BYTE logical_cell_id;
		BYTE logical_cell_presentation_info;
		BYTE elementary_cell_field_length;
		vector<BYTE> elementary_cell_idList;
		BYTE cell_linkage_info;
		//cell_linkage_info == 0x01
		WORD bouquet_id;
		//cell_linkage_info == 0x02,0x03,0x04
		WORD original_network_id;
		WORD transport_stream_id;
		WORD service_id;
		//cell_linkage_info == 0x04
		WORD event_id;
	}CELL_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE mosaic_entry_point;
	BYTE number_of_horizontal_elementary_cells;
	BYTE number_of_vertical_elementary_cells;
	vector<CELL_DATA*> cellList;

public:
	CMosaicDesc(void);
	~CMosaicDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );

protected:
	void Clear();
};
