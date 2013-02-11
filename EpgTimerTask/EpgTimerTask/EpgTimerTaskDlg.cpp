
// EpgTimerTaskDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "EpgTimerTask.h"
#include "EpgTimerTaskDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEpgTimerTaskDlg ダイアログ




CEpgTimerTaskDlg::CEpgTimerTaskDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEpgTimerTaskDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = (HICON)LoadImage( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDR_MAINFRAME ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_hIcon2 = (HICON)LoadImage( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDR_MAINFRAME ), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	m_hIconRed = (HICON)LoadImage( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_ICON_RED ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_hIconBlue = (HICON)LoadImage( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_ICON_BLUE ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_hIconGreen = (HICON)LoadImage( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_ICON_GREEN ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	m_hIconGray = (HICON)LoadImage( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_ICON_GRAY ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
}

void CEpgTimerTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CEpgTimerTaskDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_WINDOWPOSCHANGING()
	ON_BN_CLICKED(IDC_BUTTON_END, &CEpgTimerTaskDlg::OnBnClickedButtonEnd)
	ON_BN_CLICKED(IDC_BUTTON_S4, &CEpgTimerTaskDlg::OnBnClickedButtonS4)
	ON_BN_CLICKED(IDC_BUTTON_S3, &CEpgTimerTaskDlg::OnBnClickedButtonS3)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CEpgTimerTaskDlg メッセージ ハンドラー

BOOL CEpgTimerTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	wstring pipeName = L"";
	wstring pipeEventName = L"";
	Format(pipeName, L"\\\\.\\pipe\\EpgTimerGUI_Ctrl_BonPipe_%d", GetCurrentProcessId());
	Format(pipeEventName, L"Global\\EpgTimerGUI_Ctrl_BonConnect_%d", GetCurrentProcessId());

	m_cPipe.StartServer(pipeEventName.c_str(), pipeName.c_str(), OutsideCmdCallback, this);

	//ウインドウの復元
	WINDOWPLACEMENT Pos;
	Pos.length = sizeof(WINDOWPLACEMENT);
	Pos.flags = NULL;
	Pos.showCmd = SW_HIDE;
	Pos.rcNormalPosition.left = 0;
	Pos.rcNormalPosition.right = 0;
	Pos.rcNormalPosition.top = 0;
	Pos.rcNormalPosition.bottom = 0;
	SetWindowPlacement(&Pos);

	CString strBuff=L"";
	if( AddTaskBar( GetSafeHwnd(),
			WM_TRAY_PUSHICON,
			TRAYICON_ID,
			m_hIconBlue,
			strBuff ) == FALSE ){
				SetTimer(RETRY_ADD_TRAY, 5000, NULL);
	}

	CSendCtrlCmd cmd;
    if( cmd.SendRegistGUI(GetCurrentProcessId()) != CMD_SUCCESS ){
		MessageBox(L"EpgTimerSrv.exeの起動を確認できませんでした。\r\n終了してください。");
	}

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CEpgTimerTaskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CEpgTimerTaskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEpgTimerTaskDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	lpwndpos->flags &= ~SWP_SHOWWINDOW;
	CDialogEx::OnWindowPosChanging(lpwndpos);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
}


BOOL CEpgTimerTaskDlg::AddTaskBar(HWND hWnd, UINT uiMsg, UINT uiID, HICON hIcon, CString strTips)
{ 
	BOOL bRet;
	NOTIFYICONDATA stData;
	ZeroMemory(&stData, sizeof(NOTIFYICONDATA));

	stData.cbSize = sizeof(NOTIFYICONDATA); 
	stData.hWnd = hWnd; 
	stData.uID = uiID; 
	stData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
	stData.uCallbackMessage = uiMsg; 
	stData.hIcon = hIcon; 

	if( strTips.IsEmpty() == false ){
		wcsncpy_s(stData.szTip, sizeof(stData.szTip), strTips.GetBuffer(0), sizeof(stData.szTip) );
	}
 
	bRet = Shell_NotifyIcon(NIM_ADD, &stData);
  
	return bRet; 
}

BOOL CEpgTimerTaskDlg::ChgTipsTaskBar(HWND hWnd, UINT uiID, HICON hIcon, CString strTips)
{ 
	BOOL bRet;
	NOTIFYICONDATA stData;
	ZeroMemory(&stData, sizeof(NOTIFYICONDATA));

	stData.cbSize = sizeof(NOTIFYICONDATA); 
	stData.hWnd = hWnd; 
	stData.uID = uiID; 
	stData.hIcon = hIcon; 
	stData.uFlags = NIF_ICON | NIF_TIP; 

	if( strTips.IsEmpty() == false ){
		wcsncpy_s(stData.szTip, sizeof(stData.szTip), strTips.GetBuffer(0), sizeof(stData.szTip) );
	}
 
	bRet = Shell_NotifyIcon(NIM_MODIFY, &stData); 
 
	return bRet; 
}

BOOL CEpgTimerTaskDlg::DeleteTaskBar(HWND hWnd, UINT uiID)
{ 
	BOOL bRet=TRUE; 
	NOTIFYICONDATA stData; 
	ZeroMemory(&stData, sizeof(NOTIFYICONDATA));
 
	stData.cbSize = sizeof(NOTIFYICONDATA); 
	stData.hWnd = hWnd; 
	stData.uID = uiID; 
         
	bRet = Shell_NotifyIcon(NIM_DELETE, &stData); 
	return bRet; 
}


LRESULT CEpgTimerTaskDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	switch(message){
		case WM_TRAY_PUSHICON:
			{
				//タスクトレイ関係
				switch(LOWORD(lParam)){
					case WM_RBUTTONDOWN:
						{
							CMenu menu;
							CPoint point;
							menu.LoadMenu(IDR_MENU_TRAY);
							CMenu* pPopup = menu.GetSubMenu(0);

							GetCursorPos(&point);
							SetForegroundWindow();
							pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
							pPopup->DestroyMenu();
						}
						break;
					default :
						break ;
					}
			}
			break;
		case WM_QUERY_SUSPEND:
			{
				CQueryWaitDlg cDlg;
				if( cDlg.DoModal() != IDCANCEL ){
					CSendCtrlCmd cmd;
					cmd.SendSuspend((WORD)wParam);
				}
			}
			break;
		case WM_QUERY_REBOOT:
			{
				CQueryWaitDlg cDlg;
				cDlg.SetRebootMode();
				if( cDlg.DoModal() != IDCANCEL ){
					CSendCtrlCmd cmd;
					cmd.SendReboot();
				}
			}
			break;
		default:
			break;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CEpgTimerTaskDlg::OnBnClickedButtonEnd()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	EndDialog(0);
}

void CEpgTimerTaskDlg::OnBnClickedButtonS3()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CSendCtrlCmd cmd;
	if(cmd.SendChkSuspend() != 1 ){
		MessageBox(L"スタンバイに移行できる状態ではありません。\r\n（もうすぐ予約が始まる。または抑制条件のexeが起動している。など）");
	}else{
		cmd.SendSuspend(0xFF01);
	}
}

void CEpgTimerTaskDlg::OnBnClickedButtonS4()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CSendCtrlCmd cmd;
	if(cmd.SendChkSuspend() != 1 ){
		MessageBox(L"休止に移行できる状態ではありません。\r\n（もうすぐ予約が始まる。または抑制条件のexeが起動している。など）");
	}else{
		cmd.SendSuspend(0xFF02);
	}
}


void CEpgTimerTaskDlg::OnDestroy()
{
	KillTimer(RETRY_ADD_TRAY);
	KillTimer(RETRY_CHG_TRAY);
	DeleteTaskBar(GetSafeHwnd(), TRAYICON_ID);

	CSendCtrlCmd cmd;
    cmd.SendUnRegistGUI(GetCurrentProcessId());

	CDialogEx::OnDestroy();

	// TODO: ここにメッセージ ハンドラー コードを追加します。
}


void CEpgTimerTaskDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if( nIDEvent == RETRY_ADD_TRAY ){
		KillTimer(RETRY_ADD_TRAY);
		CString strBuff=L"";
/*		RESERVE_DATA Item;
		if( GetNextReserve(&Item) == TRUE ){
			wstring strTime;
			GetTimeString3(Item.StartTime, Item.dwDurationSec, strTime);

			strBuff += L"次の予約 ";
			strBuff += strTime.c_str();
			strBuff += L" ";
			strBuff += Item.strTitle.c_str();
		}else{
			strBuff += L"次の予約 なし";
		}*/
		HICON hSetIcon = m_hIconBlue;
		switch(m_dwSrvStatus){
			case 1:
				hSetIcon = m_hIconRed;
				break;
			case 2:
				hSetIcon = m_hIconGreen;
				break;
			default:
				break;
		}
		if( AddTaskBar( GetSafeHwnd(),
				WM_TRAY_PUSHICON,
				TRAYICON_ID,
				hSetIcon,
				strBuff ) == FALSE ){
					SetTimer(RETRY_ADD_TRAY, 5000, NULL);
		}
	}else if( nIDEvent == RETRY_CHG_TRAY ){
		KillTimer(RETRY_CHG_TRAY);
		CString strBuff=L"";
/*		RESERVE_DATA Item;
		if( GetNextReserve(&Item) == TRUE ){
			wstring strTime;
			GetTimeString3(Item.StartTime, Item.dwDurationSec, strTime);

			strBuff += L"次の予約 ";
			strBuff += strTime.c_str();
			strBuff += L" ";
			strBuff += Item.strTitle.c_str();
		}else{
			strBuff += L"次の予約 なし";
		}
*/
		HICON hSetIcon = m_hIconBlue;
		switch(m_dwSrvStatus){
			case 1:
				hSetIcon = m_hIconRed;
				break;
			case 2:
				hSetIcon = m_hIconGreen;
				break;
			default:
				break;
		}
		if( ChgTipsTaskBar( GetSafeHwnd(),
				TRAYICON_ID,
				hSetIcon,
				strBuff ) == FALSE ){
					SetTimer(RETRY_CHG_TRAY, 5000, NULL);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

int CALLBACK CEpgTimerTaskDlg::OutsideCmdCallback(void* pParam, CMD_STREAM* pCmdParam, CMD_STREAM* pResParam)
{
	CEpgTimerTaskDlg* pSys = (CEpgTimerTaskDlg*)pParam;
	pResParam->param = CMD_NON_SUPPORT;
	switch( pCmdParam->param ){
		case CMD2_TIMER_GUI_VIEW_EXECUTE:
			pSys->CmdViewExecute(pCmdParam, pResParam);
			break;
		case CMD2_TIMER_GUI_QUERY_SUSPEND:
			pSys->CmdViewQuerySuspend(pCmdParam, pResParam);
			break;
		case CMD2_TIMER_GUI_QUERY_REBOOT:
			pSys->CmdViewQueryReboot(pCmdParam, pResParam);
			break;
		case CMD2_TIMER_GUI_SRV_STATUS_NOTIFY2:
			pSys->CmdSrvStatusChg(pCmdParam, pResParam);
			break;
		default:
			pResParam->param = CMD_NON_SUPPORT;
			break;
	}

	return 0;
}

//CMD_TIMER_GUI_VIEW_EXECUTE Viewアプリ（EpgDataCap_Bon.exe）を起動
void CEpgTimerTaskDlg::CmdViewExecute(CMD_STREAM* pCmdParam, CMD_STREAM* pResParam)
{
	OutputDebugString(L"CEpgTimerTaskDlg::CmdViewExecute");
	wstring exeCmd = L"";

	ReadVALUE(&exeCmd, pCmdParam->data, pCmdParam->dataSize, NULL);

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	if( exeCmd.find(L".bat") != string::npos ){
		si.wShowWindow |= SW_SHOWMINNOACTIVE;
		si.dwFlags |= STARTF_USESHOWWINDOW;
	}

	BOOL bRet = CreateProcess( NULL, (WCHAR*)exeCmd.c_str(), NULL, NULL, FALSE, GetPriorityClass(GetCurrentProcess()), NULL, NULL, &si, &pi );
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	if( bRet == TRUE ){
		pResParam->dataSize = GetVALUESize(pi.dwProcessId);
		pResParam->data = new BYTE[pResParam->dataSize];
		WriteVALUE(pi.dwProcessId, pResParam->data, pResParam->dataSize, NULL);
		pResParam->param = CMD_SUCCESS;
	}else{
		pResParam->param = CMD_ERR;
	}
}

//CMD_TIMER_GUI_QUERY_SUSPEND スタンバイ、休止、シャットダウンに入っていいかの確認をユーザーに行う
void CEpgTimerTaskDlg::CmdViewQuerySuspend(CMD_STREAM* pCmdParam, CMD_STREAM* pResParam)
{
	OutputDebugString(L"CEpgTimerTaskDlg::CmdViewQuerySuspend");
	WORD val = 0;
	ReadVALUE(&val, pCmdParam->data, pCmdParam->dataSize, NULL);

	PostMessage(WM_QUERY_SUSPEND, val, 0);

	pResParam->param = CMD_SUCCESS;
}

//CMD_TIMER_GUI_QUERY_REBOOT PC再起動に入っていいかの確認をユーザーに行う
void CEpgTimerTaskDlg::CmdViewQueryReboot(CMD_STREAM* pCmdParam, CMD_STREAM* pResParam)
{
	OutputDebugString(L"CEpgTimerTaskDlg::CmdViewQueryReboot");
	WORD val = 0;
	ReadVALUE(&val, pCmdParam->data, pCmdParam->dataSize, NULL);

	PostMessage(WM_QUERY_REBOOT, val, 0);

	pResParam->param = CMD_SUCCESS;
}

//CMD2_TIMER_GUI_SRV_STATUS_NOTIFY2 サーバーのステータス変更通知
void CEpgTimerTaskDlg::CmdSrvStatusChg(CMD_STREAM* pCmdParam, CMD_STREAM* pResParam)
{
	OutputDebugString(L"CEpgTimerTaskDlg::CmdSrvStatusChg");
	WORD ver = 0;
	DWORD readSize = 0;
	ReadVALUE2(CMD_VER, &ver, pCmdParam->data, pCmdParam->dataSize, &readSize);
	NOTIFY_SRV_INFO status;
	if( ReadVALUE2(ver, &status, pCmdParam->data+readSize, pCmdParam->dataSize-readSize, NULL) == TRUE ){
		switch(status.notifyID){
		case NOTIFY_UPDATE_SRV_STATUS:
			{
				CString strBuff = L"";
				HICON hSetIcon = m_hIconBlue;
				switch(status.param1){
					case 1:
						hSetIcon = m_hIconRed;
						break;
					case 2:
						hSetIcon = m_hIconGreen;
						break;
					default:
						break;
				}
				m_dwSrvStatus = status.param1;
				if( ChgTipsTaskBar( GetSafeHwnd(),
						TRAYICON_ID,
						hSetIcon,
						strBuff ) == FALSE ){
							SetTimer(RETRY_CHG_TRAY, 5000, NULL);
				}
			}
			break;
		default:
			break;
		}
		pResParam->param = CMD_SUCCESS;
	}else{
		pResParam->param = CMD_ERR;
	}
}
