#pragma once

#include "BonCtrlDef.h"
#include "../Common/SendTSTCPDllUtil.h"

class CSendTCP
{
public:
	CSendTCP(void);
	~CSendTCP(void);

	BOOL StartUpload( vector<NW_SEND_INFO>* List );
	void SendData(BYTE* pbBuff, DWORD dwSize);
	BOOL CloseUpload();

protected:
	CSendTSTCPDllUtil m_cTcp;
};
