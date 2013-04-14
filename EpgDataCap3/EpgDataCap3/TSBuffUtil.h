#pragma once

#include "TSPacketUtil.h"

#define ERR_ADD_NEXT		100
#define ERR_NOT_SUPPORT		101

class CTSBuffUtil
{
public:
	CTSBuffUtil(void);
	~CTSBuffUtil(void);

	DWORD Add188TS(CTSPacketUtil* tsPacket);
	BOOL GetSectionBuff(BYTE** sectionData, WORD* dataSize);

protected:
	typedef struct _SECTION_BUFF{
		WORD dataSize;
		BYTE* data;
		WORD copySize;
		_SECTION_BUFF(void){
			dataSize = 0;
			data = NULL;
			copySize = 0;
		};
		~_SECTION_BUFF(void){
			SAFE_DELETE_ARRAY(data);
		};
	}SECTION_BUFF;
	vector<SECTION_BUFF*> packetList;

	WORD lastPID;
	BYTE lastCounter;
	BOOL duplicateFlag;

	SECTION_BUFF* creatingBuff;
	SECTION_BUFF* lastGetBuff;
protected:
	void Clear();
	BOOL CheckCounter(CTSPacketUtil* tsPacket);
	DWORD AddSectionBuff(CTSPacketUtil* tsPacket);
};
