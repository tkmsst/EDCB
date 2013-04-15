#pragma once

/*
6.2.7 拡張形式イベント記述子（Extended event descriptor）
拡張形式イベント記述子は、短形式イベント記述子に付け加えて使用され、イベントの
詳細記述を提供する。1 イベントに関して256 バイト長以上の情報の伝送を可能とする為
に、１つ以上の拡張形式イベント記述子を使用することができる。文書情報は項目名フィ
ールドと項目記述フィールドの2 つの欄から構成される。この構造の典型的な適用法は配
役のリストの提供である。たとえば、項目名フィールドには「プロデューサー」、項目記
述フィールドにはプロデューサーの名前が記載される。

extended_event_descriptor(){
	descriptor_tag				8 uimsbf
	descriptor_length			8 uimsbf
	descriptor_number			4 uimsbf
	last_descriptor_number		4 uimsbf
	ISO_639_language_code		24 bslbf
	length_of_items				8 uimsbf
	for ( i=0;i<N;i++){
		item_description_length		8 uimsbf
		for (j=0;j<N;j++){
			item_description_char		8 uimsbf
		}
		item_length					8 uimsbf
		for (j=0;j<N;j++){
			item_char					8 uimsbf
		}
	}
	text_length					8 uimsbf
	for (i=0;i<N;i++){
		text_char					8 uimsbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
descriptor_number（記述子番号）：記述子の番号を表す4 ビットのフィールドである。
ひとつの記述子には入りきらない情報を関係づける為に使われる。関係づけられている拡
張形式イベント記述子セットの一番目の記述子番号は、「0x0」とする。このセクション内
で拡張形式イベント記述子が加わるごとに記述子番号は1 加算される。
last_descriptor_number（最終記述子番号）：この4 ビットのフィールドは、この記述子
がその一部分となっている、関係づけられた記述子セットの最終拡張形式イベント記述子
（最大の記述子番号を持つ記述子）の番号を示す。
ISO_639_language_code（言語コード）：この24 ビットのフィールドは、コンポーネン
ト（音声、あるいはデータ）の言語、およびこの記述子に含まれる文字記述の言語を識別
する。言語コードは、ISO 639-2(22)に規定されるアルファベット3 文字コードで表す。各
文字はISO 8859-1(24)に従って8 ビットで符号化され、その順で24 ビットフィールドに挿
入される。
例： 日本語はアルファベット3 文字コードで「jpn」であり、次のように符号化される。
「0110 1010 0111 0000 0110 1110」
length_of_items（項目長）：これは8 ビットのフィールドで、後続の項目のバイト長を示
す。
item_description_length（項目名長）：これは8 ビットのフィールドで、項目名のバイト
長を示す。
item_description_char（項目名（文字符号））：これは8 ビットのフィールドで、一連の
項目名のフィールドは、項目名の文字記述を規定する。文字情報の符号化に関しては、付
録A を参照。
item_length（項目記述長）：これは8 ビットのフィールドで、項目記述のバイト長を示す。
item_char（項目記述（文字符号））：これは8 ビットのフィールドで、一連の項目記述の
フィールドは、項目の文字記述を規定する。文字情報の符号化に関しては、付録A を参照。
text_length（拡張記述長）：これは8 ビットのフィールドで、項目無しの拡張記述のバイ
ト長を示す。
text_char（拡張記述（文字符号））：これは8 ビットのフィールドで、一連の拡張記述の
フィールドは、項目無しの文字記述を規定する。文字情報の符号化に関しては、付録A を
参照。
*/

#include "../../../Common/Util.h"

class CExtendedEventDesc
{
public:
	typedef struct _ITEM_DATA{
		BYTE item_description_length;
		CHAR* item_description_char;
		BYTE item_length;
		CHAR* item_char;
		//=オペレーターの処理
		_ITEM_DATA(void){
			item_description_length = 0;
			item_description_char = NULL;
			item_length = 0;
			item_char = NULL;
		}
		~_ITEM_DATA(void){
			SAFE_DELETE_ARRAY(item_description_char);
			SAFE_DELETE_ARRAY(item_char);
		}
	}ITEM_DATA;

	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE descriptor_number;
	BYTE last_descriptor_number;
	CHAR ISO_639_language_code[4];
	BYTE length_of_items;
	vector<ITEM_DATA*> itemList;
	BYTE text_length;
	CHAR* text_char;
public:
	CExtendedEventDesc(void);
	~CExtendedEventDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );

protected:
	void Clear();
};
