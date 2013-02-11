#pragma once
#include "afxwin.h"

#include "../../Common/ParseChText5.h"

// CSetDlgEpg ダイアログ

class CSetDlgEpg : public CDialog
{
	DECLARE_DYNAMIC(CSetDlgEpg)

public:
	CSetDlgEpg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSetDlgEpg();
	
	void SetIniPath(CString commonIniPath, CString appIniPath){
		this->commonIniPath = commonIniPath;
		this->appIniPath = appIniPath;
	};
	void SaveIni(void);

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SET_EPG };
	
protected:
	CString commonIniPath;
	CString appIniPath;
	CParseChText5 chSet;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CCheckListBox serviceList;
	CButton btnBS;
	CButton btnCS1;
	CButton btnCS2;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonAllChk();
	afx_msg void OnBnClickedButtonVideoChk();
	afx_msg void OnBnClickedButtonAllClear();
};
