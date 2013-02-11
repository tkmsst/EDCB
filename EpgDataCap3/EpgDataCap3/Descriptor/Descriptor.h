#pragma once

#include "../../../Common/Util.h"
#include "DescriptorDef.h"

class CDescriptor
{
public:
	CDescriptor(void);
	~CDescriptor(void);

	BOOL Decode( BYTE* data, DWORD dataSize, vector<DESCRIPTOR_DATA*>* descriptorList, DWORD* decodeReadSize );
protected:
	void Clear(vector<DESCRIPTOR_DATA*>* descriptorList);
};
