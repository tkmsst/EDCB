// QueryWaitDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "EpgTimerTask.h"
#include "QueryWaitDlg.h"
#include "afxdialogex.h"


// CQueryWaitDlg ダイアログ

IMPLEMENT_DYNAMIC(CQueryWaitDlg, CDialogEx)

CQueryWaitDlg::CQueryWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQueryWaitDlg::IDD, pParent)
	, msgText(_T(""))
{
	m_bReboot = FALSE;
}

CQueryWaitDlg::~CQueryWaitDlg()
{
}

void CQueryWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_MSG, msgText);
	DDX_Control(pDX, IDC_PROGRESS1, waitProg);
}


BEGIN_MESSAGE_MAP(CQueryWaitDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CQueryWaitDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CQueryWaitDlg メッセージ ハンドラー


BOOL CQueryWaitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	ModifyStyleEx(0, WS_EX_DLGMODALFRAME);

	ShowWindow(SW_SHOW);
	SetForegroundWindow();
	if( m_bReboot == FALSE ){
		waitProg.SetRange(0,15);
		waitProg.SetPos(15);
		dwCount = 15;
		msgText = L"スタンバイ、休止、またはシャットダウンへ移行を行います";
	}else{
		msgText = L"PCを再起動します";
		SetWindowText(L"PC再起動");
		waitProg.SetRange(0,30);
		waitProg.SetPos(30);
		dwCount = 30;
	}
	SetTimer(TIMER_WAIT_SLEEP, 1000, NULL );
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CQueryWaitDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if( nIDEvent == TIMER_WAIT_SLEEP ){
		if( dwCount == 0 ){
			KillTimer(TIMER_WAIT_SLEEP);
			EndDialog(IDOK);
		}
		dwCount--;
		waitProg.SetPos(dwCount);
		UpdateData(FALSE);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CQueryWaitDlg::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnCancel();
}
