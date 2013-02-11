#pragma once


#include "../../Common/PathUtil.h"

#include "SetDlgBasic.h"
#include "SetDlgNetwork.h"
#include "SetDlgApp.h"
#include "SetDlgEpg.h"
#include "SetDlgAppBtn.h"
#include "SetDlgService.h"

#include "afxcmn.h"

// CSettingDlg ダイアログ

class CSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSettingDlg();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	CString commonIniPath;
	CString appIniPath;

	CSetDlgBasic basicDlg;
	CSetDlgApp appDlg;
	CSetDlgNetwork networkDlg;
	CSetDlgEpg epgDlg;
	CSetDlgAppBtn appBtnDlg;
	CSetDlgService serviceDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTcnSelchangingTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl dlgTab;
};
