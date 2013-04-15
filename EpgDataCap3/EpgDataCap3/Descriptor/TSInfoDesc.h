#pragma once

/*
6.2.42 TS 情報記述子（TS information descriptor）
TS 情報記述子は、当該TS に割り当てられるリモコンボタン識別の指定と、階層伝送時
に、サービス識別と伝送階層の対応関係を示す。表6-82 参照。

ts_information_descriptor(){
	descriptor_tag 8 uimsbf
	descriptor_length 8 uimsbf
	remote_control_key_id 8 uimsbf
	length_of_ts_name 6 uimsbf
	transmission_type_count 2 uimsbf
	for (i = 0;i< length_of_ts_name;i++) {
		ts_name_char 8 uimsbf
	}
	for (j = 0;j< transmission_type_count;j++) {
		transmission_type_info 8 bslbf
		num_of_service 8 uimsbf
		for (k = 0;k< num_of_service;k++) {
			service_id 16 uimsbf
		}
	}
	for (l = 0;l< N;l++) {
		reserved_future_use 8 bslbf
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
remote_control_key_id(リモコンキー識別)：この８ビットのフィールドは、当該ＴＳをど
のリモコンボタン番号に割り当てるか推奨値を示す。
length_of_ts_name（TS 名記述長）：これは６ビットのフィールドで、TS 名記述のバイ
ト長を示す。
transmission_type_count（伝送種別数）：これは２ビットのフィールドで、後続の伝送種
別情報に関するループ数を示す。
ts_name_char（TS 名記述）：これは８ビットのフィールドである。一連のTS 名記述の
フィールドは、当該ＴＳの名称が記述される。文字情報の符号化に関しては、付録Ａを参
照。
transmission_type_info(伝送種別情報)：これは８ビットのフィールドであり、伝送階層の
区別などに用いられるが、内容は事業者の運用規定によって定められる。
num_of_service(サービス数)：これは８ビットのフィールドで後続のサービス識別のルー
プ数を示す。
service_id（サービス識別）：これは１６ビットのフィールドで、どの伝送種別の階層で、
どのサービス識別が伝送されているかを示す。

*/

#include "../../../Common/Util.h"

class CTSInfoDesc
{
public:
	typedef struct _TRANSMISSION_DATA{
		BYTE transmission_type_info;
		BYTE num_of_service;
		vector<WORD> service_idList;
	} TRANSMISSION_DATA;
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE remote_control_key_id;
	BYTE length_of_ts_name;
	BYTE transmission_type_count;
	CHAR* ts_name_char;
	vector<TRANSMISSION_DATA> transmissionList;
public:
	CTSInfoDesc(void);
	~CTSInfoDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
