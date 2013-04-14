#include "StdAfx.h"
#include "ExtendedEventDesc.h"

CExtendedEventDesc::CExtendedEventDesc(void)
{
	text_length = 0;
	text_char = NULL;
}

CExtendedEventDesc::~CExtendedEventDesc(void)
{
	Clear();
	SAFE_DELETE_ARRAY(text_char);
}

void CExtendedEventDesc::Clear()
{
	for( size_t i=0; i<itemList.size(); i++ ){
		SAFE_DELETE(itemList[i]);
	}
	itemList.clear();
}

BOOL CExtendedEventDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}
	Clear();
	SAFE_DELETE_ARRAY(text_char);
	text_length = 0;

	//////////////////////////////////////////////////////
	//サイズのチェック
	//最低限descriptor_tagとdescriptor_lengthのサイズは必須
	if( dataSize < 2 ){
		return FALSE;
	}
	//->サイズのチェック

	DWORD readSize = 0;
	//////////////////////////////////////////////////////
	//解析処理
	descriptor_tag = data[0];
	descriptor_length = data[1];
	readSize += 2;

	if( descriptor_tag != 0x4E ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CExtendedEventDesc:: descriptor_tag err 0x4E != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CExtendedEventDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		descriptor_number = (data[readSize]&0xF0)>>4;
		last_descriptor_number = (data[readSize]&0x0F);
		readSize++;
		memcpy(ISO_639_language_code, data + readSize, 3 );
		ISO_639_language_code[3] = '\0';
		readSize+=3;
		length_of_items = data[readSize];
		readSize++;
		if( readSize + length_of_items > dataSize ){
			//サイズ異常
			_OutputDebugString( L"++++CExtendedEventDesc:: size err2 %d > %d", readSize+length_of_items, dataSize );
			return FALSE;
		}
		BYTE itemReadSize = 0;
		while(itemReadSize < length_of_items){
			ITEM_DATA* item = new ITEM_DATA;

			item->item_description_length = data[readSize];
			readSize++;
			item->item_description_char = new CHAR[item->item_description_length+1];
			memcpy(item->item_description_char, data+readSize, item->item_description_length);
			item->item_description_char[item->item_description_length] = '\0';
			readSize+=item->item_description_length;

			item->item_length = data[readSize];
			readSize++;
			item->item_char = new CHAR[item->item_length+1];
			memcpy(item->item_char, data+readSize, item->item_length);
			item->item_char[item->item_length] = '\0';
			readSize+=item->item_length;

			itemList.push_back(item);

			itemReadSize += item->item_description_length + item->item_length +2;
		}
		text_length = data[readSize];
		readSize++;
		if( readSize + text_length > dataSize ){
			//サイズ異常
			_OutputDebugString( L"++++CExtendedEventDesc:: size err3 %d > %d", readSize + text_length, dataSize );
			return FALSE;
		}
		text_char = new CHAR[text_length+1];
		memcpy(text_char, data+readSize, text_length);
		text_char[text_length] = '\0';
		readSize+=text_length;
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}

