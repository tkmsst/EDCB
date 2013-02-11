
// EpgTimerTaskDlg.h : ヘッダー ファイル
//

#pragma once
#include "../../Common/Util.h"
#include "../../Common/StringUtil.h"
#include "../../Common/PathUtil.h"
#include "../../Common/PipeServer.h"
#include "../../Common/SendCtrlCmd.h"
#include "../../Common/CtrlCmdUtil.h"
#include "../../Common/CtrlCmdUtil2.h"
#include "QueryWaitDlg.h"

#define WM_TRAY_PUSHICON (WM_USER+51) //トレイアイコン押された
#define WM_QUERY_SUSPEND (WM_USER+52)
#define WM_QUERY_REBOOT (WM_USER+53)

#define TRAYICON_ID 200
#define RETRY_ADD_TRAY 1000
#define RETRY_CHG_TRAY 1001

// CEpgTimerTaskDlg ダイアログ
class CEpgTimerTaskDlg : public CDialogEx
{
// コンストラクション
public:
	CEpgTimerTaskDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_EPGTIMERTASK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

protected:
	//タスクトレイ
	BOOL DeleteTaskBar(HWND hWnd, UINT uiID);
	BOOL AddTaskBar(HWND hWnd, UINT uiMsg, UINT uiID, HICON hIcon, CString strTips);
	BOOL ChgTipsTaskBar(HWND hWnd, UINT uiID, HICON hIcon, CString strTips);

// 実装
protected:
	HICON m_hIcon;
	HICON m_hIcon2;
	HICON m_hIconRed;
	HICON m_hIconBlue;
	HICON m_hIconGreen;
	HICON m_hIconGray;

	CPipeServer m_cPipe;
	DWORD m_dwSrvStatus;

	//外部制御コマンド関係
	static int CALLBACK OutsideCmdCallback(void* pParam, CMD_STREAM* pCmdParam, CMD_STREAM* pResParam);
	//CMD_TIMER_GUI_VIEW_EXECUTE Viewアプリ（EpgDataCap_Bon.exe）を起動
	void CmdViewExecute(CMD_STREAM* pCmdParam, CMD_STREAM* pResParam);
	//CMD_TIMER_GUI_QUERY_SUSPEND スタンバイ、休止、シャットダウンに入っていいかの確認をユーザーに行う
	void CmdViewQuerySuspend(CMD_STREAM* pCmdParam, CMD_STREAM* pResParam);
	//CMD_TIMER_GUI_QUERY_REBOOT PC再起動に入っていいかの確認をユーザーに行う
	void CmdViewQueryReboot(CMD_STREAM* pCmdParam, CMD_STREAM* pResParam);
	//CMD_TIMER_GUI_SRV_STATUS_CHG サーバーのステータス変更通知（1:通常、2:EPGデータ取得開始、3:予約録画開始）
	void CmdSrvStatusChg(CMD_STREAM* pCmdParam, CMD_STREAM* pResParam);

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonEnd();
	afx_msg void OnBnClickedButtonS4();
	afx_msg void OnBnClickedButtonS3();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
