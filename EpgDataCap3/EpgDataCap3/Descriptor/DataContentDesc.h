#pragma once

/*
6.2.28 データコンテンツ記述子（Data content descriptor）
データコンテンツ記述子（表 6－48 参照）は、データ放送番組の個々のコンテンツに関
する詳細情報の記述に使用される。

data_content_descriptor(){
	descriptor_tag			8 uimsbf
	descriptor_length		8 uimsbf
	data_component_id		16 uimsbf
	entry_component			8 uimsbf
	selector_length			8 uimsbf
	for(i=0;i<N;i++){
		selector_byte			8 uimsbf
	}
	num_of_component_ref	8 uimsbf
	for(i=0;i<num_of_component_ref;i++){
		component_ref			8 uimsbf
	}
	ISO_639_language_code	24 bslbf
	text_length				8 uimsbf
	for(i=0;i<N;i++){
		text_char				8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
data_component_id（データ符号化方式識別）：これは16 ビットのフィールドで、データ
符号化方式記述子のデータ符号化方式識別と同じ値を記述する。
entry_component（エントリコンポーネント）：この8 ビットのフィールドでは、データ
放送のコンテンツを構成する複数のコンポーネントストリームのうち、最初に参照される
べきデータを含むコンポーネントストリームを、コンポーネントタグを用いて指定する。
selector_length（セレクタ長）：この8 ビットのフィールドは、後続のセレクタ領域のバ
イト長を規定する。
selector_byte（セレクタバイト）：これは8 ビットのフィールドである。一連のセレクタ
領域は、データを取得するために必要な情報を記述する。この領域に記述される情報のデ
ータ構造はデータ符号化方式毎に別途規定する。（付録J 参照）
num_of_component_ref（参照コンポーネント数）：この8 ビットのフィールドは、この
記述子の表すコンテンツの記録再生に必要な、イベント内の全コンポーネントストリーム
（ただしエントリコンポーネントで指定されたコンポーネントストリームを除く）の個数
を表す。この個数は後続の参照コンポーネントのループのバイト長と一致する。
component_ref（参照コンポーネント）：この8 ビットのフィールドは、当該コンテンツ
の視聴もしくは記録に必要なイベント内のコンポーネントストリーム（ただしエントリコ
ンポーネントで指定されたコンポーネントストリームを除く）のコンポーネントタグを記
述する。
ISO_639_language_code（言語コード）：この24 ビットのフィールドは、後続のサービ
ス記述で使用される文字記述の言語をISO 639-2(22)に規定されるアルファベット3 文字コ
ードで表す。
text_length（コンテンツ記述長）：この8 ビットのフィールドは後続のコンテンツ記述の
バイト長を表す。
text_char（コンテンツ記述）：これは8 ビットのフィールドである。一連の文字情報フィ
ールドは、伝送されるコンテンツに関する説明を記述する。

*/

#include "../../../Common/Util.h"

class CDataContentDesc
{
public:
	BYTE descriptor_tag;
	BYTE descriptor_length;
	WORD data_component_id;
	BYTE entry_component;
	BYTE selector_length;
	BYTE* selector_byte;
	BYTE num_of_component_ref;
	BYTE* component_ref;
	CHAR ISO_639_language_code[4];
	BYTE text_length;
	CHAR* text_char;
public:
	CDataContentDesc(void);
	~CDataContentDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
