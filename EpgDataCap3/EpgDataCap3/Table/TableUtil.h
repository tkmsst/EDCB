#pragma once

#include "../../../Common/Util.h"
#include "TableUtilDef.h"

class CTableUtil
{
public:
	CTableUtil(void);
	~CTableUtil(void);

	BOOL Decode( BYTE* data, DWORD dataSize, vector<TABLE_DATA*>* tableList, DWORD* decodeReadSize );
protected:
	void Clear(vector<TABLE_DATA*>* tableList);
};
