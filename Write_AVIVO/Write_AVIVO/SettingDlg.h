#pragma once

#include "../../Common/StringUtil.h"
#include "../../Common/PathUtil.h"
#include "DShowCtrl.h"

class CSettingDlg
{
public:
	CSettingDlg(void);
	~CSettingDlg(void);

	DWORD CreateSettingDialog(HINSTANCE hInstance);

protected:

protected:

	static LRESULT CALLBACK DlgProc(HWND hDlgWnd, UINT msg, WPARAM wp, LPARAM lp);

};

