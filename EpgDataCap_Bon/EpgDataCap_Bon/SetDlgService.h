#pragma once
#include "afxwin.h"

#include "../../Common/PathUtil.h"
#include "../../Common/StringUtil.h"
#include "../../Common/ParseChText4.h"


// CSetDlgService ダイアログ

class CSetDlgService : public CDialog
{
	DECLARE_DYNAMIC(CSetDlgService)

public:
	CSetDlgService(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSetDlgService();

	void SetIniPath(CString commonIniPath, CString appIniPath){
		this->commonIniPath = commonIniPath;
		this->appIniPath = appIniPath;
	};
	void SaveIni(void);

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SET_SERVICE };


protected:
	CString commonIniPath;
	CString appIniPath;

	typedef struct _CH_SET_INFO{
		wstring bonFile;
		wstring chSetPath;
		CParseChText4 chSet;
	}CH_SET_INFO;
	map<wstring, CH_SET_INFO*> chList;
	wstring lastSelect;

	BOOL FindBonFileName(wstring src, wstring& dllName);
	void ReloadList();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CComboBox combBon;
	CCheckListBox listService;
	afx_msg void OnBnClickedButtonChkAll();
	afx_msg void OnBnClickedButtonChkVideo();
	afx_msg void OnBnClickedButtonChkClear();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboBon();
	afx_msg void OnChkChange();
	CEdit editCh;
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnLbnSelchangeListService();
};
