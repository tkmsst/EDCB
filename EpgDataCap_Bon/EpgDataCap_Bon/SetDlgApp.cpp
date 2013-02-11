// SetDlgApp.cpp : 実装ファイル
//

#include "stdafx.h"
#include "EpgDataCap_Bon.h"
#include "SetDlgApp.h"
#include "afxdialogex.h"


// CSetDlgApp ダイアログ

IMPLEMENT_DYNAMIC(CSetDlgApp, CDialog)

CSetDlgApp::CSetDlgApp(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlgApp::IDD, pParent)
	, startMargine(0)
	, endMargine(0)
	, epgCapBackStartWaitSec(0)
{

}

CSetDlgApp::~CSetDlgApp()
{
}

void CSetDlgApp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ENABLE_DECODE, btnEnableScramble);
	DDX_Control(pDX, IDC_CHECK_NEED_CAPTION, btnNeedCaption);
	DDX_Control(pDX, IDC_CHECK_NEED_DATA, btnNeedData);
	DDX_Text(pDX, IDC_EDIT_START_MARGINE, startMargine);
	DDX_Text(pDX, IDC_EDIT_END_MARGINE, endMargine);
	DDX_Control(pDX, IDC_CHECK_OVER_WRITE, btnOverWrite);
	DDX_Control(pDX, IDC_CHECK_ALL_SERVICE, btnAllService);
	DDX_Control(pDX, IDC_CHECK_EPGCAP_LIVE, btnEpgCapLive);
	DDX_Control(pDX, IDC_CHECK_EPGCAP_REC, btnEpgCapRec);
	DDX_Control(pDX, IDC_CHECK_TASKMIN, btnTaskMin);
	DDX_Control(pDX, IDC_CHECK_EMM, btnEnableEMM);
	DDX_Control(pDX, IDC_CHECK_OPENLAST, btnOpenLast);
	DDX_Text(pDX, IDC_EDIT_BACKSTART_WAITSEC, epgCapBackStartWaitSec);
}


BEGIN_MESSAGE_MAP(CSetDlgApp, CDialog)
END_MESSAGE_MAP()


// CSetDlgApp メッセージ ハンドラー


BOOL CSetDlgApp::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください

	btnAllService.SetCheck( GetPrivateProfileInt( L"SET", L"AllService", 0, appIniPath ) );
	btnEnableScramble.SetCheck( GetPrivateProfileInt( L"SET", L"Scramble", 1, appIniPath ) );
	btnEnableEMM.SetCheck( GetPrivateProfileInt( L"SET", L"EMM", 0, appIniPath ) );
	btnNeedCaption.SetCheck( GetPrivateProfileInt( L"SET", L"Caption", 1, appIniPath ) );
	btnNeedData.SetCheck( GetPrivateProfileInt( L"SET", L"Data", 0, appIniPath ) );

	startMargine = GetPrivateProfileInt( L"SET", L"StartMargine", 5, appIniPath );
	endMargine = GetPrivateProfileInt( L"SET", L"EndMargine", 5, appIniPath );
	btnOverWrite.SetCheck( GetPrivateProfileInt( L"SET", L"OverWrite", 0, appIniPath ) );
	
	btnEpgCapLive.SetCheck( GetPrivateProfileInt( L"SET", L"EpgCapLive", 1, appIniPath ) );
	btnEpgCapRec.SetCheck( GetPrivateProfileInt( L"SET", L"EpgCapRec", 1, appIniPath ) );
	btnTaskMin.SetCheck( GetPrivateProfileInt( L"SET", L"MinTask", 0, appIniPath ) );
	btnOpenLast.SetCheck( GetPrivateProfileInt( L"SET", L"OpenLast", 1, appIniPath ) );

	epgCapBackStartWaitSec = GetPrivateProfileInt( L"SET", L"EpgCapBackStartWaitSec", 30, appIniPath );

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CSetDlgApp::SaveIni(void)
{
	UpdateData(TRUE);

	CString val = L"";
	val.Format(L"%d",btnAllService.GetCheck());
	WritePrivateProfileString( L"SET", L"AllService", val.GetBuffer(0), appIniPath );
	val.Format(L"%d",btnEnableScramble.GetCheck());
	WritePrivateProfileString( L"SET", L"Scramble", val.GetBuffer(0), appIniPath );
	val.Format(L"%d",btnEnableEMM.GetCheck());
	WritePrivateProfileString( L"SET", L"EMM", val.GetBuffer(0), appIniPath );
	val.Format(L"%d",btnNeedCaption.GetCheck());
	WritePrivateProfileString( L"SET", L"Caption", val.GetBuffer(0), appIniPath );
	val.Format(L"%d",btnNeedData.GetCheck());
	WritePrivateProfileString( L"SET", L"Data", val.GetBuffer(0), appIniPath );

	val.Format(L"%d",startMargine);
	WritePrivateProfileString( L"SET", L"StartMargine", val.GetBuffer(0), appIniPath );
	val.Format(L"%d",endMargine);
	WritePrivateProfileString( L"SET", L"EndMargine", val.GetBuffer(0), appIniPath );

	val.Format(L"%d",btnOverWrite.GetCheck());
	WritePrivateProfileString( L"SET", L"OverWrite", val.GetBuffer(0), appIniPath );

	val.Format(L"%d",btnEpgCapLive.GetCheck());
	WritePrivateProfileString( L"SET", L"EpgCapLive", val.GetBuffer(0), appIniPath );
	val.Format(L"%d",btnEpgCapRec.GetCheck());
	WritePrivateProfileString( L"SET", L"EpgCapRec", val.GetBuffer(0), appIniPath );
	val.Format(L"%d",btnTaskMin.GetCheck());
	WritePrivateProfileString( L"SET", L"MinTask", val.GetBuffer(0), appIniPath );
	val.Format(L"%d",btnOpenLast.GetCheck());
	WritePrivateProfileString( L"SET", L"OpenLast", val.GetBuffer(0), appIniPath );

	val.Format(L"%d",epgCapBackStartWaitSec);
	WritePrivateProfileString( L"SET", L"EpgCapBackStartWaitSec", val.GetBuffer(0), appIniPath );

}


BOOL CSetDlgApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if( pMsg->message == WM_KEYDOWN ){
		if( pMsg->wParam  == VK_RETURN || pMsg->wParam  == VK_ESCAPE ){
			return FALSE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
