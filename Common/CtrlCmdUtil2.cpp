#include "stdafx.h"
#include "CtrlCmdUtil2.h"
#include "Util.h"


DWORD GetVALUESize2(WORD ver, char val )
{
	return sizeof(char);
}

BOOL WriteVALUE2(WORD ver, char val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(char) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(char));
	if( writeSize != NULL ){
		*writeSize = sizeof(char);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, char* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(char) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(char*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(char);
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, unsigned char val )
{
	return sizeof(unsigned char);
}

BOOL WriteVALUE2(WORD ver, unsigned char val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(unsigned char) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(unsigned char));
	if( writeSize != NULL ){
		*writeSize = sizeof(unsigned char);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, unsigned char* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(unsigned char) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(unsigned char*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(unsigned char);
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, short val )
{
	return sizeof(short);
}

BOOL WriteVALUE2(WORD ver, short val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(short) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(short));
	if( writeSize != NULL ){
		*writeSize = sizeof(short);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, short* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(short) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(short*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(short);
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, unsigned short val )
{
	return sizeof(unsigned short);
}

BOOL WriteVALUE2(WORD ver, unsigned short val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(unsigned short) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(unsigned short));
	if( writeSize != NULL ){
		*writeSize = sizeof(unsigned short);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, unsigned short* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(unsigned short) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(unsigned short*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(unsigned short);
	}
	return TRUE;
}


DWORD GetVALUESize2(WORD ver, int val )
{
	return sizeof(int);
}

BOOL WriteVALUE2(WORD ver, int val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(int) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(int));
	if( writeSize != NULL ){
		*writeSize = sizeof(int);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, int* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(int) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(int*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(int);
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, unsigned int val )
{
	return sizeof(unsigned int);
}

BOOL WriteVALUE2(WORD ver, unsigned int val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(unsigned int) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(unsigned int));
	if( writeSize != NULL ){
		*writeSize = sizeof(unsigned int);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, unsigned int* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(unsigned int) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(unsigned int*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(unsigned int);
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, long val )
{
	return sizeof(long);
}

BOOL WriteVALUE2(WORD ver, long val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(long) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(long));
	if( writeSize != NULL ){
		*writeSize = sizeof(long);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, long* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(long) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(long*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(long);
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, unsigned long val )
{
	return sizeof(unsigned long);
}

BOOL WriteVALUE2(WORD ver, unsigned long val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(unsigned long) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(unsigned long));
	if( writeSize != NULL ){
		*writeSize = sizeof(unsigned long);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, unsigned long* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(unsigned long) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(unsigned long*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(unsigned long);
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, __int64 val )
{
	return sizeof(__int64);
}

BOOL WriteVALUE2(WORD ver, __int64 val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(__int64) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(__int64));
	if( writeSize != NULL ){
		*writeSize = sizeof(__int64);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, __int64* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(__int64) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(__int64*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(__int64);
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, unsigned __int64 val )
{
	return sizeof(unsigned __int64);
}

BOOL WriteVALUE2(WORD ver, unsigned __int64 val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( buff == NULL || sizeof(unsigned __int64) > buffSize ){
		return FALSE;
	}
	memcpy(buff, &val, sizeof(unsigned __int64));
	if( writeSize != NULL ){
		*writeSize = sizeof(unsigned __int64);
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, unsigned __int64* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( buff == NULL || sizeof(unsigned __int64) > buffSize ){
		return FALSE;
	}
	if( val != NULL ){
		*val = *(unsigned __int64*)buff;
	}
	if( readSize != NULL ){
		*readSize = sizeof(unsigned __int64);
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<unsigned short>* val)
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	size += sizeof(unsigned short) * (DWORD)val->size();

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<unsigned short>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valueSize = GetVALUESize2(ver, val );
	if( buff == NULL || valueSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valueSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, (*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<unsigned short>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		unsigned short data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<unsigned long>* val)
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	size += sizeof(unsigned long) * (DWORD)val->size();

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<unsigned long>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valueSize = GetVALUESize2(ver, val );
	if( buff == NULL || valueSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valueSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, (*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<unsigned long>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		unsigned long data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<__int64>* val)
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	size += sizeof(__int64) * (DWORD)val->size();

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<__int64>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valueSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valueSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valueSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, (*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<__int64>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		__int64 data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, wstring val )
{
	return ( (DWORD)val.size() + 1 ) * sizeof(WCHAR) + sizeof(DWORD);
}

BOOL WriteVALUE2(WORD ver, wstring val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD stringBuffSize = GetVALUESize2(ver, val );
	if( buff == NULL || stringBuffSize > buffSize ){
		return FALSE;
	}

	ZeroMemory( buff, stringBuffSize );
	//まず全体のサイズ
	DWORD size = 0;
	if( WriteVALUE2(ver, stringBuffSize, buff, stringBuffSize, &size ) == FALSE ){
		return FALSE;
	}
	//文字あれば
	if( val.size() > 0 ){
		memcpy(buff + size, val.c_str(), val.size()*sizeof(WCHAR));
	}
	if( writeSize != NULL ){
		*writeSize = stringBuffSize;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, wstring* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	
	*val = (WCHAR*)(buff + size);

	if( readSize != NULL ){
		*readSize = valSize;
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<wstring>* val )
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	for( size_t i=0; i<val->size(); i++ ){
		size += GetVALUESize2(ver,(*val)[i]);
	}

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<wstring>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, (*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<wstring>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		wstring data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, SYSTEMTIME* val )
{
	return sizeof( SYSTEMTIME );
}

BOOL WriteVALUE2(WORD ver, SYSTEMTIME* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	if( val == NULL || buff == NULL || sizeof( SYSTEMTIME ) > buffSize ){
		return FALSE;
	}
	memcpy(buff, val, sizeof( SYSTEMTIME ));
	if( writeSize != NULL ){
		*writeSize = sizeof( SYSTEMTIME );
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, SYSTEMTIME* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || sizeof( SYSTEMTIME ) > buffSize ){
		return FALSE;
	}
	*val = *(SYSTEMTIME*)buff;
	if( readSize != NULL ){
		*readSize = sizeof( SYSTEMTIME );
	}
	return TRUE;
}

DWORD GetVALUESize2(WORD ver, REC_FILE_SET_INFO* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver,val->recFolder);
	size += GetVALUESize2(ver,val->writePlugIn);
	size += GetVALUESize2(ver,val->recNamePlugIn);
	size += GetVALUESize2(ver,val->recFileName);
	if( ver>=2 ){
		goto CMD_END;
	}

CMD_END:
	return size;
}

BOOL WriteVALUE2(WORD ver, REC_FILE_SET_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if(val != NULL ){
		if( WriteVALUE2(ver, val->recFolder, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->writePlugIn, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->recNamePlugIn, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->recFileName, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, REC_FILE_SET_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->recFolder, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->writePlugIn, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recNamePlugIn, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recFileName, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<REC_FILE_SET_INFO>* val )
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	for( size_t i=0; i<val->size(); i++ ){
		size += GetVALUESize2(ver,&(*val)[i]);
	}

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<REC_FILE_SET_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, &(*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<REC_FILE_SET_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		REC_FILE_SET_INFO data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, REC_SETTING_DATA* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver,val->recMode);
	size += GetVALUESize2(ver,val->priority);
	size += GetVALUESize2(ver,val->tuijyuuFlag);
	size += GetVALUESize2(ver,val->serviceMode);
	size += GetVALUESize2(ver,val->pittariFlag);
	size += GetVALUESize2(ver,val->batFilePath);
	size += GetVALUESize2(ver,&val->recFolderList);
	size += GetVALUESize2(ver,val->suspendMode);
	size += GetVALUESize2(ver,val->rebootFlag);
	size += GetVALUESize2(ver,val->useMargineFlag);
	size += GetVALUESize2(ver,val->startMargine);
	size += GetVALUESize2(ver,val->endMargine);
	size += GetVALUESize2(ver,val->continueRecFlag);
	size += GetVALUESize2(ver,val->partialRecFlag);
	size += GetVALUESize2(ver,val->tunerID);
	size += GetVALUESize2(ver,&val->partialRecFolder);
	if( ver>=2 ){
		goto CMD_END;
	}

CMD_END:
	return size;
}

BOOL WriteVALUE2(WORD ver, REC_SETTING_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if (val != NULL ){
		if( WriteVALUE2(ver, val->recMode, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->priority, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->tuijyuuFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->serviceMode, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->pittariFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->batFilePath, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->recFolderList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->suspendMode, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->rebootFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->useMargineFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->startMargine, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->endMargine, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->continueRecFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->partialRecFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->tunerID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->partialRecFolder, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, REC_SETTING_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->recMode, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->priority, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->tuijyuuFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->serviceMode, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->pittariFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->batFilePath, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recFolderList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->suspendMode, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->rebootFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->useMargineFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->startMargine, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->endMargine, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->continueRecFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->partialRecFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->tunerID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->partialRecFolder, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, RESERVE_DATA* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver,val->title);
	size += GetVALUESize2(ver,&val->startTime);
	size += GetVALUESize2(ver,val->durationSecond);
	size += GetVALUESize2(ver,val->stationName);
	size += GetVALUESize2(ver,val->originalNetworkID);
	size += GetVALUESize2(ver,val->transportStreamID);
	size += GetVALUESize2(ver,val->serviceID);
	size += GetVALUESize2(ver,val->eventID);
	size += GetVALUESize2(ver,val->comment);
	size += GetVALUESize2(ver,val->reserveID);
	size += GetVALUESize2(ver,val->recWaitFlag);
	size += GetVALUESize2(ver,val->overlapMode);
	size += GetVALUESize2(ver,val->recFilePath);
	size += GetVALUESize2(ver,&val->startTimeEpg);
	size += GetVALUESize2(ver,&val->recSetting);
	size += GetVALUESize2(ver,val->reserveStatus);

	if( ver<=4 ){
		goto CMD_END;
	}

	size += GetVALUESize2(ver,&val->recFileNameList);
	size += GetVALUESize2(ver,val->param1);

	if( ver>=5 ){
		goto CMD_END;
	}

CMD_END:
	return size;
}

BOOL WriteVALUE2(WORD ver, RESERVE_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if(val != NULL ){
		if( WriteVALUE2(ver, val->title, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->startTime, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->durationSecond, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->stationName, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->originalNetworkID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->transportStreamID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->serviceID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->eventID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->comment, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->reserveID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->recWaitFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->overlapMode, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->recFilePath, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->startTimeEpg, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->recSetting, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->reserveStatus, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver<=4 ){
			goto CMD_END;
		}

		if( WriteVALUE2(ver, &val->recFileNameList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->param1, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=5 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, RESERVE_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->title, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->startTime, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->durationSecond, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->stationName, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->originalNetworkID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->transportStreamID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->serviceID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->eventID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->comment, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->reserveID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recWaitFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->overlapMode, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recFilePath, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->startTimeEpg, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recSetting, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->reserveStatus, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver<=4 ){
			goto CMD_END;
		}

		if( ReadVALUE2(ver, &val->recFileNameList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->param1, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<RESERVE_DATA>* val )
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	for( size_t i=0; i<val->size(); i++ ){
		size += GetVALUESize2(ver,&(*val)[i]);
	}

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<RESERVE_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, &(*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<RESERVE_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		RESERVE_DATA data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<RESERVE_DATA*>* val )
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	for( size_t i=0; i<val->size(); i++ ){
		size += GetVALUESize2(ver,(*val)[i]);
	}

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<RESERVE_DATA*>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, (*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<RESERVE_DATA*>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		RESERVE_DATA* data = new RESERVE_DATA;
		if( ReadVALUE2(ver, data, buff + pos, buffSize - pos, &size ) == FALSE ){
			SAFE_DELETE(data);
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, NOTIFY_SRV_INFO* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver,val->notifyID);
	size += GetVALUESize2(ver,&val->time);
	size += GetVALUESize2(ver,val->param1);
	size += GetVALUESize2(ver,val->param2);
	size += GetVALUESize2(ver,val->param3);
	size += GetVALUESize2(ver,val->param4);
	size += GetVALUESize2(ver,val->param5);
	size += GetVALUESize2(ver,val->param6);
	if( ver>=2 ){
		goto CMD_END;
	}

CMD_END:
	return size;
}

BOOL WriteVALUE2(WORD ver, NOTIFY_SRV_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if(val != NULL ){
		if( WriteVALUE2(ver, val->notifyID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->time, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->param1, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->param2, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->param3, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->param4, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->param5, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->param6, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, NOTIFY_SRV_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->notifyID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->time, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->param1, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->param2, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->param3, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->param4, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->param5, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->param6, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, EPGDB_CONTENT_DATA* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver, val->content_nibble_level_1);
	size += GetVALUESize2(ver, val->content_nibble_level_2);
	size += GetVALUESize2(ver, val->user_nibble_1);
	size += GetVALUESize2(ver, val->user_nibble_2);

	return size;
}

BOOL WriteVALUE2(WORD ver, EPGDB_CONTENT_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if(val != NULL ){
		if( WriteVALUE2(ver, val->content_nibble_level_1, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->content_nibble_level_2, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->user_nibble_1, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->user_nibble_2, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, EPGDB_CONTENT_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->content_nibble_level_1, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->content_nibble_level_2, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->user_nibble_1, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->user_nibble_2, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<EPGDB_CONTENT_DATA>* val )
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	for( size_t i=0; i<val->size(); i++ ){
		size += GetVALUESize2(ver,&(*val)[i]);
	}

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<EPGDB_CONTENT_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, &(*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<EPGDB_CONTENT_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		EPGDB_CONTENT_DATA data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, EPGDB_SEARCH_DATE_INFO* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver, val->startDayOfWeek);
	size += GetVALUESize2(ver, val->startHour);
	size += GetVALUESize2(ver, val->startMin);
	size += GetVALUESize2(ver, val->endDayOfWeek);
	size += GetVALUESize2(ver, val->endHour);
	size += GetVALUESize2(ver, val->endMin);

	return size;
}

BOOL WriteVALUE2(WORD ver, EPGDB_SEARCH_DATE_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if(val != NULL ){
		if( WriteVALUE2(ver, val->startDayOfWeek, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->startHour, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->startMin, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->endDayOfWeek, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->endHour, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->endMin, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, EPGDB_SEARCH_DATE_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->startDayOfWeek, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->startHour, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->startMin, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->endDayOfWeek, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->endHour, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->endMin, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<EPGDB_SEARCH_DATE_INFO>* val )
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	for( size_t i=0; i<val->size(); i++ ){
		size += GetVALUESize2(ver,&(*val)[i]);
	}

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<EPGDB_SEARCH_DATE_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, &(*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<EPGDB_SEARCH_DATE_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		EPGDB_SEARCH_DATE_INFO data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, EPGDB_SEARCH_KEY_INFO* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver, val->andKey);
	size += GetVALUESize2(ver, val->notKey);
	size += GetVALUESize2(ver, val->regExpFlag);
	size += GetVALUESize2(ver, val->titleOnlyFlag);
	size += GetVALUESize2(ver, &val->contentList);
	size += GetVALUESize2(ver, &val->dateList);
	size += GetVALUESize2(ver, &val->serviceList);
	size += GetVALUESize2(ver, &val->videoList);
	size += GetVALUESize2(ver, &val->audioList);
	size += GetVALUESize2(ver, val->aimaiFlag);
	size += GetVALUESize2(ver, val->notContetFlag);
	size += GetVALUESize2(ver, val->notDateFlag);
	size += GetVALUESize2(ver, val->freeCAFlag);
	if( ver<=2 ){
		goto CMD_END;
	}
	size += GetVALUESize2(ver, val->chkRecEnd);
	size += GetVALUESize2(ver, val->chkRecDay);
	if( ver>=3 ){
		goto CMD_END;
	}
CMD_END:
	return size;
}

BOOL WriteVALUE2(WORD ver, EPGDB_SEARCH_KEY_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if(val != NULL ){
		if( WriteVALUE2(ver, val->andKey, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->notKey, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->regExpFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->titleOnlyFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->contentList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->dateList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->serviceList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->videoList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->audioList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->aimaiFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->notContetFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->notDateFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->freeCAFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ver<=2 ){
			goto CMD_END;
		}
		if( WriteVALUE2(ver, val->chkRecEnd, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->chkRecDay, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ver>=3 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, EPGDB_SEARCH_KEY_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->andKey, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->notKey, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->regExpFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->titleOnlyFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->contentList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->dateList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->serviceList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->videoList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->audioList, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->aimaiFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->notContetFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->notDateFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->freeCAFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ver<=2 ){
			goto CMD_END;
		}
		if( ReadVALUE2(ver, &val->chkRecEnd, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->chkRecDay, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=3 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, EPG_AUTO_ADD_DATA* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver,val->dataID);
	size += GetVALUESize2(ver,&val->searchInfo);
	size += GetVALUESize2(ver,&val->recSetting);

	if( ver<=4 ){
		goto CMD_END;
	}

	size += GetVALUESize2(ver,val->addCount);

	if( ver>=5 ){
		goto CMD_END;
	}

CMD_END:
	return size;
}

BOOL WriteVALUE2(WORD ver, EPG_AUTO_ADD_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if(val != NULL ){
		if( WriteVALUE2(ver, val->dataID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->searchInfo, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->recSetting, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver<=4 ){
			goto CMD_END;
		}

		if( WriteVALUE2(ver, val->addCount, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=5 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, EPG_AUTO_ADD_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->dataID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->searchInfo, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recSetting, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver<=4 ){
			goto CMD_END;
		}

		if( ReadVALUE2(ver, &val->addCount, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=5 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<EPG_AUTO_ADD_DATA>* val )
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	for( size_t i=0; i<val->size(); i++ ){
		size += GetVALUESize2(ver,&(*val)[i]);
	}

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<EPG_AUTO_ADD_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, &(*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<EPG_AUTO_ADD_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		EPG_AUTO_ADD_DATA data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, MANUAL_AUTO_ADD_DATA* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver, val->dataID);
	size += GetVALUESize2(ver, val->dayOfWeekFlag);
	size += GetVALUESize2(ver, val->startTime);
	size += GetVALUESize2(ver, val->durationSecond);
	size += GetVALUESize2(ver, val->title);
	size += GetVALUESize2(ver, val->stationName);
	size += GetVALUESize2(ver, val->originalNetworkID);
	size += GetVALUESize2(ver, val->transportStreamID);
	size += GetVALUESize2(ver, val->serviceID);
	size += GetVALUESize2(ver, &val->recSetting);

	return size;
}

BOOL WriteVALUE2(WORD ver, MANUAL_AUTO_ADD_DATA* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if(val != NULL ){
		if( WriteVALUE2(ver, val->dataID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->dayOfWeekFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->startTime, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->durationSecond, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->title, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->stationName, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->originalNetworkID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->transportStreamID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->serviceID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->recSetting, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, MANUAL_AUTO_ADD_DATA* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->dataID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->dayOfWeekFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->startTime, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->durationSecond, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->title, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->stationName, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->originalNetworkID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->transportStreamID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->serviceID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recSetting, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=2 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<MANUAL_AUTO_ADD_DATA>* val )
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	for( size_t i=0; i<val->size(); i++ ){
		size += GetVALUESize2(ver,&(*val)[i]);
	}

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<MANUAL_AUTO_ADD_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, &(*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<MANUAL_AUTO_ADD_DATA>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		MANUAL_AUTO_ADD_DATA data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, REC_FILE_INFO* val )
{
	DWORD size = sizeof(DWORD);
	if( val == NULL ){
		return size;
	}

	size += GetVALUESize2(ver, val->id);
	size += GetVALUESize2(ver, val->recFilePath);
	size += GetVALUESize2(ver, val->title);
	size += GetVALUESize2(ver, &val->startTime);
	size += GetVALUESize2(ver, val->durationSecond);
	size += GetVALUESize2(ver, val->serviceName);
	size += GetVALUESize2(ver, val->originalNetworkID);
	size += GetVALUESize2(ver, val->transportStreamID);
	size += GetVALUESize2(ver, val->serviceID);
	size += GetVALUESize2(ver, val->eventID);
	size += GetVALUESize2(ver, val->drops);
	size += GetVALUESize2(ver, val->scrambles);
	size += GetVALUESize2(ver, val->recStatus);
	size += GetVALUESize2(ver, &val->startTimeEpg);
	size += GetVALUESize2(ver, val->comment);
	size += GetVALUESize2(ver, val->programInfo);
	size += GetVALUESize2(ver, val->errInfo);
	if( ver<=3 ){
		goto CMD_END;
	}
	size += GetVALUESize2(ver, val->protectFlag);
	if( ver>=4 ){
		goto CMD_END;
	}

CMD_END:
	return size;
}

BOOL WriteVALUE2(WORD ver, REC_FILE_INFO* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	if(val != NULL ){
		if( WriteVALUE2(ver, val->id, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->recFilePath, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->title, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->startTime, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->durationSecond, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->serviceName, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->originalNetworkID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->transportStreamID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->serviceID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->eventID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->drops, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->scrambles, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->recStatus, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, &val->startTimeEpg, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->comment, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->programInfo, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( WriteVALUE2(ver, val->errInfo, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver<=3 ){
			goto CMD_END;
		}

		if( WriteVALUE2(ver, val->protectFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=4 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( writeSize != NULL ){
		*writeSize = pos;
	}
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, REC_FILE_INFO* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD) ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}

	if( pos < valSize ){
		if( ReadVALUE2(ver, &val->id, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recFilePath, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->title, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->startTime, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->durationSecond, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->serviceName, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->originalNetworkID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->transportStreamID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->serviceID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->eventID, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->drops, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->scrambles, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->recStatus, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->startTimeEpg, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->comment, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->programInfo, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ReadVALUE2(ver, &val->errInfo, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		if( ver<=3 ){
			goto CMD_END;
		}

		if( ReadVALUE2(ver, &val->protectFlag, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;

		if( ver>=4 ){
			goto CMD_END;
		}
	}

CMD_END:
	if( readSize != NULL ){
		*readSize = valSize;
	}

	return TRUE;
}

DWORD GetVALUESize2(WORD ver, vector<REC_FILE_INFO>* val )
{
	DWORD size = sizeof(DWORD)*2;
	if( val == NULL ){
		return size;
	}

	for( size_t i=0; i<val->size(); i++ ){
		size += GetVALUESize2(ver,&(*val)[i]);
	}

	return size;
}

BOOL WriteVALUE2(WORD ver, vector<REC_FILE_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* writeSize )
{
	DWORD valSize = GetVALUESize2(ver, val );
	if( val == NULL || buff == NULL || valSize > buffSize ){
		return FALSE;
	}

	//まず全体のサイズ
	DWORD pos = 0;
	DWORD size = 0;
	if( WriteVALUE2(ver, valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	DWORD count = 0;
	if( val != NULL ){
		count = (DWORD)val->size();
	}
	//リストの個数
	if( WriteVALUE2(ver, count, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	
	if( val != NULL ){
		//リストの中身
		for( DWORD i=0; i < (DWORD)val->size(); i++ ){
			if( WriteVALUE2(ver, &(*val)[i], buff + pos, buffSize - pos, &size ) == FALSE ){
				return FALSE;
			}
			pos += size;
		}
	}

	if( writeSize != NULL ){
		*writeSize = pos;
	}
	
	return TRUE;
}

BOOL ReadVALUE2(WORD ver, vector<REC_FILE_INFO>* val, BYTE* buff, DWORD buffSize, DWORD* readSize )
{
	if( val == NULL || buff == NULL || buffSize < sizeof(DWORD)*2 ){
		return FALSE;
	}

	DWORD pos = 0;
	DWORD size = 0;
	DWORD valSize = 0;
	DWORD valCount = 0;
	//全体のサイズ
	if( ReadVALUE2(ver, &valSize, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;
	if( buffSize < valSize ){
		return FALSE;
	}
	//リストの個数
	if( ReadVALUE2(ver, &valCount, buff + pos, buffSize - pos, &size ) == FALSE ){
		return FALSE;
	}
	pos += size;

	for( DWORD i= 0; i<valCount; i++ ){
		REC_FILE_INFO data;
		if( ReadVALUE2(ver, &data, buff + pos, buffSize - pos, &size ) == FALSE ){
			return FALSE;
		}
		pos += size;
		val->push_back( data );
	}

	if( readSize != NULL ){
		*readSize = pos;
	}

	return TRUE;
}
