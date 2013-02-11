#pragma once
#include "afxwin.h"


// CSetDlgBasic ダイアログ

class CSetDlgBasic : public CDialog
{
	DECLARE_DYNAMIC(CSetDlgBasic)

public:
	CSetDlgBasic(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSetDlgBasic();

	void SetIniPath(CString commonIniPath, CString appIniPath){
		this->commonIniPath = commonIniPath;
		this->appIniPath = appIniPath;
	};
	void SaveIni(void);


// ダイアログ データ
	enum { IDD = IDD_DIALOG_SET_BASIC };

protected:
	CString commonIniPath;
	CString appIniPath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRecPath();
	afx_msg void OnBnClickedButtonRecAdd();
	afx_msg void OnBnClickedButtonRecDel();
	afx_msg void OnBnClickedButtonRecUp();
	afx_msg void OnBnClickedButtonRecDown();
	afx_msg void OnBnClickedButtonSetPath();
	CString settingFolderPath;
	CString recFolderPath;
	CListBox recFolderList;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};
