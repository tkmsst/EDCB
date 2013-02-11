#pragma once

#include "afxwin.h"
#include "afxcmn.h"


#include "../../BonCtrl/BonCtrlDef.h"

// CSetDlgNetwork ダイアログ

class CSetDlgNetwork : public CDialog
{
	DECLARE_DYNAMIC(CSetDlgNetwork)

public:
	CSetDlgNetwork(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSetDlgNetwork();

	void SetIniPath(CString commonIniPath, CString appIniPath){
		this->commonIniPath = commonIniPath;
		this->appIniPath = appIniPath;
	};
	void SaveIni(void);

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SET_NW };

protected:
	CString commonIniPath;
	CString appIniPath;

	vector<NW_SEND_INFO> udpSendList;
	vector<NW_SEND_INFO> tcpSendList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListBox udpList;
	CIPAddressCtrl udpIP;
	UINT udpPort;
	CButton udpBroadcast;
	UINT udpWaitSec;
	UINT udpWaitPacket;
	CListBox tcpList;
	CIPAddressCtrl tcpIP;
	UINT tcpPort;
	afx_msg void OnBnClickedButtonAddUdp();
	afx_msg void OnBnClickedButtonDelUdp();
	afx_msg void OnBnClickedButtonAddTcp();
	afx_msg void OnBnClickedButtonDelTcp();
};
