#pragma once

/*
6.2.38 SI プライムTS 記述子（SI prime_ts descriptor）
SI プライムTS 記述子は、SI プライムTS（SI に関して特殊な伝送形態を持つTS）の識
別情報とその伝送パラメータを示すために用いる。表6－75 参照。

SI_prime_ts_descriptor(){
	descriptor_tag					8 uimsbf
	descriptor_length				8 uimsbf
	parameter_version				8 uimsbf
	update_time						16 uimsbf
	SI_prime_ts_network_id			16 uimsbf
	SI_prime_transport_stream_id	16 uimsbf
	for(i=0; i<N; i++){
		table_id						8 uimsbf
		table_description_length		8 uimsbf
		for(j=0; j<N; j++){
			table_description_byte			8 uimsbf
		}
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
parameter_version（パラメータバージョン）：これは８ビットのフィールドで、SI の伝
送パラメータの更新番号を示す。伝送パラメータに更新があるたびに、1 ずつ増加した値を
記載する。
update_time（更新日）：これは16 ビットのフィールドで、記載された伝送パラメータが
有効となる年月日をMJD の下位16 ビットで記載する。
SI_prime_ts_network_id（SI プライムTS ネットワーク識別）：この16 ビットのフィー
ルドは、SI プライムTS のネットワーク識別を示す。
SI_prime_transport_stream_id（SI プライムトランスポートストリーム識別）：この16
ビットのフィールドは、SI プライムTS のトランスポートストリーム識別を示す。
table_id（テーブル識別）：この8 ビットのフィールドは、後続のテーブル記述バイトの
フィールドに記述するテーブル種別を示す。
table_description_length（テーブル記述長）：この8 ビットのフィールドは、後続のテー
ブル記述バイトのバイト長を表す。
table_description_byte（テーブル記述バイト）：これは8 ビットのフィールドである。一
連のテーブル記述領域は、事業者の運用規定で定められるテーブル種別ごとの伝送パラメ
ータを記述する。

*/

#include "../../../Common/Util.h"

class CSIPrime_tsDesc
{
public:
	typedef struct _TABLE_DESC_DATA{
		BYTE table_id;
		BYTE table_description_length;
		BYTE* table_description_byte;
		_TABLE_DESC_DATA(void){
			table_description_byte = NULL;
		}
		~_TABLE_DESC_DATA(void){
			SAFE_DELETE_ARRAY(table_description_byte);
		}
	} TABLE_DESC_DATA;
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE parameter_version;
	SYSTEMTIME update_time;
	WORD SI_prime_ts_network_id;
	WORD SI_prime_transport_stream_id;
	vector<TABLE_DESC_DATA*> tableDescDataList;

public:
	CSIPrime_tsDesc(void);
	~CSIPrime_tsDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );

protected:
	void Clear();
};
