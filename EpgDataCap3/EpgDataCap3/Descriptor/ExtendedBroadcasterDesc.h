#pragma once

/*
6.2.43 拡張ブロードキャスタ記述子（Extended broadcaster descriptor）
拡張ブロードキャスタ記述子は、地上ブロードキャスタ識別などの拡張ブロードキャス
タ識別情報を指定し、他の拡張ブロードキャスタや、他ネットワークのブロードキャスタ
との関連づけを行う。表6-83 参照。

extended_broadcaster_descriptor(){
	descriptor_tag						8 uimsbf
	descriptor_length					8 uimsbf
	broadcaster_type					4 uimsbf
	reserved_future_use					4 bslbf
	if ( broadcaster_type == 0x1 ) {
		terrestrial_broadcaster_id			16 uimsbf
		number_of_affiliation_id_loop		4 uimsbf
		number_of_broadcaster_id_loop		4 uimsbf
		for( i=0; i<N1; i++ ) {
			affiliation_id						8 uimsbf
		}
		for( j=0; j<N2; j++ ) {
			original_network_id					16 uimsbf
			broadcaster_id						8 uimsbf
		}
		for( k=0; k<N3; k++ ) {
			private_data_byte					8 bslbf
		}
	}else if ( broadcaster_type == 0x2 ) {
		terrestrial_sound_broadcaster_id	16 uimsbf
		number_of_sound_broadcast_affiliation_id_loop	4 uimsbf
		number_of_broadcaster_id_loop		4 uimsbf
		for( i=0; i<N1; i++ ) {
			sound_broadcast_affiliation_id		8 uimsbf
		}
		for( j=0; j<N2; j++ ) {
			original_network_id					16 uimsbf
			broadcaster_id						8 uimsbf
		}
		for( k=0; k<N3; k++ ) {
			private_data_byte					8 bslbf
		}
	}else{
		for(i=0;i<N;i++){
			reserved_future_use					8 bslbf
		}
	}
}

descriptor_tag（記述子タグ）：記述子タグは8 ビットのフィールドで、各記述子を識別す
る。MPEG-2 規格に従った意味でのこれらの値は、ISO/IEC 13818-1(21)に記載されている。
descriptor_length（記述子長）：記述子長は8 ビットのフィールドで、このフィールドの
直後に続く記述子のデータ部分の全バイト長を規定する。
broadcaster_type（ブロードキャスタ種別）：これは４ビットのフィールドで表6-84 に従
い符号化される。
terrestrial_broadcaster_id(地上ブロードキャスタ識別)：これは１６ビットのフィールドで、
当該フィールドで記載する地上ブロードキャスタを識別する。
number_of_affiliation_id_loop（系列識別ループ数）：これは４ビットのフィールドで、
後続の系列識別のループ数を示す。
number_of_broadcaster_id_loop（ブロードキャスタ識別ループ数）：これは４ビットのフ
ィールドで、後続のブロードキャスタ識別ループのループ数を示す。
affiliation_id（系列識別）：これは８ビットのフィールドで、当該地上ブロードキャスタ
識別が、どの系列に含まれるかを識別するために用いられる。
original_network_id（オリジナルネットワーク識別）：この１６ビットのフィールドは、
元の分配システムのネットワーク識別を規定するラベルの役割をする。
broadcaster_id（ブロードキャスタ識別）：これは８ビットのフィールドで、そのオリジ
ナルネットワーク内のブロードキャスタを識別する。
terrestrial_sound_broadcaster_id(地上音声ブロードキャスタ識別)：これは１６ビットの
フィールドで、当該フィールドで記載する地上音声ブロードキャスタを識別する。
number_of_sound_broadcast_affiliation_id_loop（音声放送系列識別ループ数）：これは
４ビットのフィールドで、後続の音声放送系列識別のループ数を示す。
number_of_sound_broadcaster_id_loop（ブロードキャスタ識別ループ数）：これは４ビ
ットのフィールドで、後続の地上音声ブロードキャスタ識別ループのループ数を示す。
sound_broadcast_affiliation_id（音声放送系列識別）：これは８ビットのフィールドで、
当該地上音声ブロードキャスタ識別が、どの音声放送系列に含まれるかを識別するために
用いられる。

*/

#include "../../../Common/Util.h"

class CExtendedBroadcasterDesc
{
public:
	typedef struct _BROADCAST_DATA{
		WORD original_network_id;
		BYTE broadcaster_id;
	} BROADCAST_DATA;
	BYTE descriptor_tag;
	BYTE descriptor_length;
	BYTE broadcaster_type;
	WORD terrestrial_broadcaster_id;
	BYTE number_of_affiliation_id_loop;
	BYTE number_of_broadcaster_id_loop;
	vector<BYTE> affiliation_idList;
	vector<BROADCAST_DATA> broadcastList;
	WORD terrestrial_sound_broadcaster_id;
	BYTE number_of_sound_broadcast_affiliation_id_loop;
	vector<BYTE> sound_broadcast_affiliation_idList;
public:
	CExtendedBroadcasterDesc(void);
	~CExtendedBroadcasterDesc(void);

	BOOL Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize );
};
