#pragma once

/*
descriptor()：表12-2 で示すダウンロードコンテンツ記述子を格納する。

Download_content_descriptor () {
	descriptor_tag				8 uimsbf
	descriptor_length			8 uimsbf
	reboot						1 bslbf
	add_on						1 bslbf
	compatibility_flag			1 bslbf
	module_info_flag			1 bslbf
	text_info_flag				1 bslbf
	reserved					3 bslbf
	component_size				32 uimsbf
	download_id					32 uimsbf
	time_out_value_DII			32 uimsbf
	leak_rate					22 uimsbf
	reserved					2 bslbf
	component_tag				8 uimsbf
	if (compatibility_flag == ‘1’) {
		compatibilityDescriptor()
	}
	if (module_info_flag == ‘1’) {
		num_of_modules				16 uimsbf
		for ( i=0; i<num_of_modules; i++) {
			module_id					16 uimsbf
			module_size					32 uimsbf
			module_info_length			8 uimsbf
			for (i=0; i< module_info_length; i++) {
				module_info_byte;			8 uimsbf
			}
		}
	}
	private_data_length			8 uimsbf
	for ( i=0; i<private_data_length ; i++ ) {
		private_data_byte		8 uimsbf
	}
	if (text_info_flag == ‘1’) {
		ISO_639_language_code		24 uimsbf
		text_length					8 uimsbf
		for(i=0;i<N;i++){
			text_char					8uimsbf
		}
	}
}

descriptor_tag：ダウンロードコンテンツ記述子を示す識別値。値は0xC9。
reboot：ダウンロード終了時に受信機を再起動する必要があるか否かを指示する。
1ならば再起動、0 ならば継続動作。
add_on：既存のモジュールの書き換えなのか、追加なのかを示す。
1ならば追加、0 ならば書き換え。
compatibility_flag：記述子中のCompatibilityDescriptor()の有無を示すフラグ。
1ならばCompatibilityDescriptor()が符号化され、0 ならば符号化されない。
module_info_flag：記述子中のモジュール毎の情報の有無を示すフラグ。
1ならばモジュール毎の情報が符号化され、0 ならば符号化されない。
text_info_flag：記述子末尾のサービス記述の有無を示すフラグ。
1ならばサービス記述が符号化され、0 ならば符号化されない。
component_size(コンポーネントサイズ)：カルーセルで伝送データサイズの合計（単位はバイト）
download_id（ダウンロード識別）：このダウンロードの受け付け番号を識別する目的で設定された、
ダウンロード識別を指定する。ここで指定されたダウンロード識別は実際の配信時のDII/DDB に
も指定される。
time_out_value_DII(DII タイムアウト値)：当該カルーセルのDII の全セクション受信に対する推
奨すべきタイムアウト値(単位はミリ秒)。
leak_rate(リークレート)：受信機のトランスポートバッファのリークレート。単位は50bytes/s。
reserved（予約）：この3 ビットのフィールドは将来のための予約である。
component_tag（コンポーネントタグ）：この8 ビットのフィールドにはPMT のストリーム識別記
述子で与えられる、対応するストリームのコンポーネントタグの値が入る。
compatibilityDescriptor()：DII 内のcompatibilityDescriptor とまったく同等のものが入る。SDTT
におけるtable_id_ext/group で特定できないようなダウンロード対象の特定はここで行う。
number_of_modules：モジュールの数を示す。
module_id：ダウンロードにおけるファイル伝送に用いられるモジュール識別。
module_size：当該モジュールのバイト長を表わす。0 は不定長。
module_info_length：module_info_byte のバイト長。
module_info_byte：DII にて記述されるtype 記述子、Name 記述子、Info 記述子、Control 記述子
のうち必要なものを格納する。
private_data_length：private_data_byte のバイト長。
private_data_byte：この領域の使い方は本規格の範囲外である。
ISO_639_language_code（言語コード）：サービス記述で使用される文字記述の言語を識別する。
text_length（サービス記述長）：サービス記述の長さ（単位：バイト）
text_char（サービス記述）：伝送されるダウンロードコンテンツのサービスに関する記述

*/

#include "../../../Common/Util.h"

class CDownloadContentDesc
{
public:
	typedef struct _MODULE_INFO_DATA{
		WORD module_id;
		DWORD module_size;
		BYTE module_info_length;
		BYTE* module_info_byte;
		_MODULE_INFO_DATA(void){
			module_info_byte = NULL;
		}
		~_MODULE_INFO_DATA(void){
			SAFE_DELETE_ARRAY(module_info_byte);
		}
	} MODULE_INFO_DATA;
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE reboot;
	BYTE add_on;
	BYTE compatibility_flag;
	BYTE module_info_flag;
	BYTE text_info_flag;
	DWORD component_size;
	DWORD download_id;
	DWORD time_out_value_DII;
	DWORD leak_rate;
	BYTE component_tag;
//	BYTE* compatibilityDescriptor;
	WORD num_of_modules;
	vector<MODULE_INFO_DATA*> moduleInfoList;
	BYTE private_data_length;
//	BYTE* private_data_byte;
	CHAR ISO_639_language_code[4];
	BYTE text_length;
	BYTE* text_char;

public:
	CDownloadContentDesc(void);
	~CDownloadContentDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );

protected:
	void Clear();
};
