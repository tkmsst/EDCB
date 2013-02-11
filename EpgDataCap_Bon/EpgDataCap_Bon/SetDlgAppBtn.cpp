// SetDlgAppBtn.cpp : 実装ファイル
//

#include "stdafx.h"
#include "EpgDataCap_Bon.h"
#include "SetDlgAppBtn.h"
#include "afxdialogex.h"


// CSetDlgAppBtn ダイアログ

IMPLEMENT_DYNAMIC(CSetDlgAppBtn, CDialog)

CSetDlgAppBtn::CSetDlgAppBtn(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlgAppBtn::IDD, pParent)
	, viewExe(_T(""))
	, viewOpt(_T(""))
{

}

CSetDlgAppBtn::~CSetDlgAppBtn()
{
}

void CSetDlgAppBtn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VIEW_EXE, viewExe);
	DDX_Text(pDX, IDC_EDIT_VIEW_OPT, viewOpt);
}


BEGIN_MESSAGE_MAP(CSetDlgAppBtn, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_EXE, &CSetDlgAppBtn::OnBnClickedButtonViewExe)
END_MESSAGE_MAP()


// CSetDlgAppBtn メッセージ ハンドラー


BOOL CSetDlgAppBtn::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	WCHAR buff[512]=L"";
	GetPrivateProfileString( L"SET", L"ViewPath", L"", buff, 512, appIniPath );
	this->viewExe = buff;
	GetPrivateProfileString( L"SET", L"ViewOption", L"", buff, 512, appIniPath );
	this->viewOpt = buff;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CSetDlgAppBtn::SaveIni(void)
{
	UpdateData(TRUE);

	WritePrivateProfileString( L"SET", L"ViewPath", this->viewExe.GetBuffer(0), appIniPath );
	WritePrivateProfileString( L"SET", L"ViewOption", this->viewOpt.GetBuffer(0), appIniPath );
}

BOOL CSetDlgAppBtn::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if( pMsg->message == WM_KEYDOWN ){
		if( pMsg->wParam  == VK_RETURN || pMsg->wParam  == VK_ESCAPE ){
			return FALSE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CSetDlgAppBtn::OnBnClickedButtonViewExe()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(TRUE);
	WCHAR strFile[MAX_PATH]=L"";
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof (OPENFILENAME);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = 	TEXT("exe files (*.exe)\0*.exe\0")
					TEXT("All files (*.*)\0*.*\0\0");
	ofn.lpstrFile = strFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == 0) {
		return ;
	}
	this->viewExe = strFile;
	UpdateData(FALSE);
}
