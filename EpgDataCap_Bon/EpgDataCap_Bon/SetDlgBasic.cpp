// SetDlgBasic.cpp : 実装ファイル
//

#include "stdafx.h"
#include "EpgDataCap_Bon.h"
#include "SetDlgBasic.h"
#include "afxdialogex.h"

#include "../../Common/PathUtil.h"
#include "../../Common/StringUtil.h"

// CSetDlgBasic ダイアログ

IMPLEMENT_DYNAMIC(CSetDlgBasic, CDialog)

CSetDlgBasic::CSetDlgBasic(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlgBasic::IDD, pParent)
	, settingFolderPath(_T(""))
	, recFolderPath(_T(""))
{

}

CSetDlgBasic::~CSetDlgBasic()
{
}

void CSetDlgBasic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SET_PATH, settingFolderPath);
	DDX_Text(pDX, IDC_EDIT_REC_FOLDER, recFolderPath);
	DDX_Control(pDX, IDC_LIST_REC_FOLDER, recFolderList);
}


BEGIN_MESSAGE_MAP(CSetDlgBasic, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REC_PATH, &CSetDlgBasic::OnBnClickedButtonRecPath)
	ON_BN_CLICKED(IDC_BUTTON_REC_ADD, &CSetDlgBasic::OnBnClickedButtonRecAdd)
	ON_BN_CLICKED(IDC_BUTTON_REC_DEL, &CSetDlgBasic::OnBnClickedButtonRecDel)
	ON_BN_CLICKED(IDC_BUTTON_REC_UP, &CSetDlgBasic::OnBnClickedButtonRecUp)
	ON_BN_CLICKED(IDC_BUTTON_REC_DOWN, &CSetDlgBasic::OnBnClickedButtonRecDown)
	ON_BN_CLICKED(IDC_BUTTON_SET_PATH, &CSetDlgBasic::OnBnClickedButtonSetPath)
END_MESSAGE_MAP()


// CSetDlgBasic メッセージ ハンドラー
BOOL CSetDlgBasic::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	wstring path;
	GetSettingPath(path);
	settingFolderPath = path.c_str();

	int iNum = GetPrivateProfileInt( L"SET", L"RecFolderNum", 0, commonIniPath );
	if( iNum == 0 ){
		GetDefSettingPath(path);
		recFolderList.AddString( path.c_str() );
	}else{
		for( int i = 0; i < iNum; i++ ){
			CString key = L"";
			key.Format(L"RecFolderPath%d", i );
			WCHAR buff[512]=L"";
			GetPrivateProfileString( L"SET", key, L"", buff, 512, commonIniPath );
			recFolderList.AddString( buff );
		}
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CSetDlgBasic::SaveIni()
{
	UpdateData(TRUE);
	WritePrivateProfileString(L"SET", L"DataSavePath", settingFolderPath.GetBuffer(0), commonIniPath);
	_CreateDirectory(settingFolderPath);

	int iNum = recFolderList.GetCount();
	CString strVal;
	strVal.Format( L"%d", iNum );
	WritePrivateProfileString(L"SET", L"RecFolderNum", strVal.GetBuffer(0), commonIniPath);
	for( int i = 0; i < iNum; i++ ){
		CString strKey = L"";
		strKey.Format(L"RecFolderPath%d", i );
		CString strFolder = L"";
		recFolderList.GetText( i, strFolder );
		WritePrivateProfileString(L"SET", strKey, strFolder, commonIniPath);
	}

	UpdateData(FALSE);
}

void CSetDlgBasic::OnBnClickedButtonRecPath()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(TRUE);

	BROWSEINFO bi;
	LPWSTR lpBuffer;
	LPITEMIDLIST pidlRoot = NULL;
	LPITEMIDLIST pidlBrowse;
	LPMALLOC lpMalloc = NULL;

	HRESULT hr = SHGetMalloc(&lpMalloc);
	if(FAILED(hr)) return;

	if ((lpBuffer = (LPWSTR) lpMalloc->Alloc(_MAX_PATH*2)) == NULL) {
		return;
	}
	if( recFolderPath.IsEmpty() != 0 ){
		if (!SUCCEEDED(SHGetSpecialFolderLocation( m_hWnd,CSIDL_DESKTOP,&pidlRoot ) )){ 
			lpMalloc->Free(lpBuffer);
			return;
		}
	}

	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = pidlRoot;
	bi.pszDisplayName = lpBuffer;
	bi.lpszTitle = L"録画ファイル保存フォルダを選択してください";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = (LPARAM)recFolderPath.GetBuffer(0);

	pidlBrowse = SHBrowseForFolder(&bi);
	if (pidlBrowse != NULL) {  
		if (SHGetPathFromIDList(pidlBrowse, lpBuffer)) {
			recFolderPath = lpBuffer;
		}
		lpMalloc->Free(pidlBrowse);
	}
	if( pidlRoot != NULL ){
		lpMalloc->Free(pidlRoot); 
	}
	lpMalloc->Free(lpBuffer);
	lpMalloc->Release();
	
	UpdateData(FALSE);
}


void CSetDlgBasic::OnBnClickedButtonRecAdd()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(TRUE);
	if( recFolderPath.IsEmpty() == true ){
		return ;
	}
	wstring addPath = recFolderPath.GetBuffer(0);
	ChkFolderPath( addPath );

	//同一フォルダがすでにあるかチェック
	int iNum = recFolderList.GetCount();
	BOOL findFlag = FALSE;
	for( int i = 0; i < iNum; i++ ){
		CString folder = L"";
		recFolderList.GetText( i, folder );
		wstring strPath = folder.GetBuffer(0);
		ChkFolderPath( strPath );

		if( CompareNoCase( addPath, strPath ) == 0 ){
			findFlag = TRUE;
			break;
		}
	}
	if( findFlag == FALSE ){
		recFolderList.AddString( addPath.c_str() );
	}

	UpdateData(FALSE);
}


void CSetDlgBasic::OnBnClickedButtonRecDel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int sel = recFolderList.GetCurSel();
	if( sel == LB_ERR ){
		return ;
	}
	recFolderList.DeleteString( sel );
}


void CSetDlgBasic::OnBnClickedButtonRecUp()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int sel = recFolderList.GetCurSel();
	if( sel == LB_ERR || sel == 0){
		return ;
	}
	CString folder = L"";
	recFolderList.GetText( sel, folder );
	recFolderList.DeleteString( sel );
	recFolderList.InsertString( sel-1, folder );
	recFolderList.SetCurSel( sel-1 );
}


void CSetDlgBasic::OnBnClickedButtonRecDown()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int sel = recFolderList.GetCurSel();
	if( sel == LB_ERR || sel == recFolderList.GetCount() - 1 ){
		return ;
	}
	CString folder = L"";
	recFolderList.GetText( sel, folder );
	recFolderList.DeleteString( sel );
	recFolderList.InsertString( sel+1, folder );
	recFolderList.SetCurSel( sel+1 );
}


void CSetDlgBasic::OnBnClickedButtonSetPath()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(TRUE);

	BROWSEINFO bi;
	LPWSTR lpBuffer;
	LPITEMIDLIST pidlRoot = NULL;
	LPITEMIDLIST pidlBrowse;
	LPMALLOC lpMalloc = NULL;

	HRESULT hr = SHGetMalloc(&lpMalloc);
	if(FAILED(hr)) return;

	if ((lpBuffer = (LPWSTR) lpMalloc->Alloc(_MAX_PATH*2)) == NULL) {
		return;
	}
	if( settingFolderPath.IsEmpty() != 0 ){
		if (!SUCCEEDED(SHGetSpecialFolderLocation( m_hWnd,CSIDL_DESKTOP,&pidlRoot ) )){ 
			lpMalloc->Free(lpBuffer);
			return;
		}
	}

	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = pidlRoot;
	bi.pszDisplayName = lpBuffer;
	bi.lpszTitle = L"設定関係保存フォルダを選択してください";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = (LPARAM)settingFolderPath.GetBuffer(0);

	pidlBrowse = SHBrowseForFolder(&bi);
	if (pidlBrowse != NULL) {  
		if (SHGetPathFromIDList(pidlBrowse, lpBuffer)) {
			settingFolderPath = lpBuffer;
		}
		lpMalloc->Free(pidlBrowse);
	}
	if( pidlRoot != NULL ){
		lpMalloc->Free(pidlRoot); 
	}
	lpMalloc->Free(lpBuffer);
	lpMalloc->Release();
	
	UpdateData(FALSE);
}


BOOL CSetDlgBasic::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if( pMsg->message == WM_KEYDOWN ){
		if( pMsg->wParam  == VK_RETURN || pMsg->wParam  == VK_ESCAPE ){
			return FALSE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

