// SetDlgService.cpp : 実装ファイル
//

#include "stdafx.h"
#include "EpgDataCap_Bon.h"
#include "SetDlgService.h"
#include "afxdialogex.h"


// CSetDlgService ダイアログ

IMPLEMENT_DYNAMIC(CSetDlgService, CDialog)

CSetDlgService::CSetDlgService(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlgService::IDD, pParent)
{

}

CSetDlgService::~CSetDlgService()
{
	map<wstring, CH_SET_INFO*>::iterator itr;
	for( itr = chList.begin(); itr != chList.end(); itr++ ){
		SAFE_DELETE(itr->second);
	}
}

void CSetDlgService::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BON, combBon);
	DDX_Control(pDX, IDC_LIST_SERVICE, listService);
	DDX_Control(pDX, IDC_EDIT_CH, editCh);
}


BEGIN_MESSAGE_MAP(CSetDlgService, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHK_ALL, &CSetDlgService::OnBnClickedButtonChkAll)
	ON_BN_CLICKED(IDC_BUTTON_CHK_VIDEO, &CSetDlgService::OnBnClickedButtonChkVideo)
	ON_BN_CLICKED(IDC_BUTTON_CHK_CLEAR, &CSetDlgService::OnBnClickedButtonChkClear)
	ON_CBN_SELCHANGE(IDC_COMBO_BON, &CSetDlgService::OnCbnSelchangeComboBon)
	ON_CONTROL(CLBN_CHKCHANGE, IDC_LIST_SERVICE, OnChkChange)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CSetDlgService::OnBnClickedButtonDel)
	ON_LBN_SELCHANGE(IDC_LIST_SERVICE, &CSetDlgService::OnLbnSelchangeListService)
END_MESSAGE_MAP()


// CSetDlgService メッセージ ハンドラー


void CSetDlgService::OnBnClickedButtonChkAll()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	for( int i=0; i<this->listService.GetCount(); i++ ){
		CH_DATA4* chSet = (CH_DATA4*)listService.GetItemDataPtr(i);
		chSet->useViewFlag = TRUE;
		this->listService.SetCheck(i, TRUE);
	}
}


void CSetDlgService::OnBnClickedButtonChkVideo()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	for( int i=0; i<this->listService.GetCount(); i++ ){
		CH_DATA4* chSet = (CH_DATA4*)listService.GetItemDataPtr(i);
		if( chSet->serviceType == 0x01 || chSet->serviceType == 0xA5 ){
			chSet->useViewFlag = TRUE;
			this->listService.SetCheck(i, TRUE);
		}else{
			chSet->useViewFlag = FALSE;
			this->listService.SetCheck(i, FALSE);
		}
	}
}


void CSetDlgService::OnBnClickedButtonChkClear()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	for( int i=0; i<this->listService.GetCount(); i++ ){
		CH_DATA4* chSet = (CH_DATA4*)listService.GetItemDataPtr(i);
		chSet->useViewFlag = FALSE;
		this->listService.SetCheck(i, FALSE);
	}
}


BOOL CSetDlgService::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if( pMsg->message == WM_KEYDOWN ){
		if( pMsg->wParam  == VK_RETURN || pMsg->wParam  == VK_ESCAPE ){
			return FALSE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CSetDlgService::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください

	wstring path = L"";
	GetSettingPath(path);

	wstring srvIniPath = L"";
	GetEpgTimerSrvIniPath(srvIniPath);

	wstring searchKey = path;
	searchKey += L"\\*.ChSet4.txt";

	WIN32_FIND_DATA findData;
	HANDLE find;

	//指定フォルダのファイル一覧取得
	find = FindFirstFile( searchKey.c_str(), &findData);
	if ( find == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}
	do{
		if( (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 ){
			//本当に拡張子DLL?
			if( IsExt(findData.cFileName, L".txt") == TRUE ){
				wstring chSetPath = L"";
				Format(chSetPath, L"%s\\%s", path.c_str(), findData.cFileName);

				wstring bonFileName = L"";
				wstring buff = findData.cFileName;

				FindBonFileName(buff, bonFileName);

				bonFileName += L".dll";

				CH_SET_INFO* item = new CH_SET_INFO;
				item->bonFile = bonFileName;
				item->chSetPath = chSetPath;
				item->chSet.ParseText(chSetPath.c_str());

				chList.insert(pair<wstring, CH_SET_INFO*>(item->bonFile, item));

				combBon.AddString(item->bonFile.c_str());
			}
		}
	}while(FindNextFile(find, &findData));

	FindClose(find);
	if( chList.size() > 0 ){
		combBon.SetCurSel(0);
		ReloadList();

		CString text = L"";
		combBon.GetWindowText(text);
		lastSelect = text.GetBuffer(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CSetDlgService::ReloadList()
{
	listService.ResetContent();

	CString text = L"";
	combBon.GetWindowText(text);

	wstring key = text.GetBuffer(0);
	map<wstring, CH_SET_INFO*>::iterator itr;
	itr = chList.find(key);
	if( itr != chList.end()){
		multimap<LONGLONG, CH_DATA4>::iterator itrCh;
		for( itrCh = itr->second->chSet.chList.begin(); itrCh != itr->second->chSet.chList.end(); itrCh++ ){
			int index = listService.AddString(itrCh->second.serviceName.c_str());
			listService.SetCheck(index, itrCh->second.useViewFlag);
			listService.SetItemDataPtr(index, &itrCh->second);
		}
	}
	editCh.SetWindowText(L"");
}

BOOL CSetDlgService::FindBonFileName(wstring src, wstring& dllName)
{
	wstring buff = src;
	size_t pos = buff.rfind(L")");
	if( pos == string::npos ){
		dllName = src;
		return FALSE;
	}

	int count = 1;
	for( size_t i=pos-1; i>=0; i-- ){
		if(buff.compare(i,1,L")") == 0 ){
			count++;
		}else if(buff.compare(i,1,L"(") == 0){
			count--;
		}
		if( count == 0 ){
			dllName = buff.substr(0, i);
			break;
		}
	}

	return TRUE;
}

void CSetDlgService::SaveIni()
{
	UpdateData(TRUE);

	map<wstring, CH_SET_INFO*>::iterator itr;
	for( itr = chList.begin(); itr != chList.end(); itr++ ){
		itr->second->chSet.SaveChText();
	}

	UpdateData(FALSE);
}

void CSetDlgService::OnChkChange() 
{
	int sel = listService.GetCurSel();
	if( sel == LB_ERR ){
		return ;
	}
	CH_DATA4* chSet = (CH_DATA4*)listService.GetItemDataPtr(sel);
	chSet->useViewFlag = listService.GetCheck(sel);
}

void CSetDlgService::OnCbnSelchangeComboBon()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int sel = combBon.GetCurSel();
	if( sel == CB_ERR ){
		return;
	}
	ReloadList();
}


void CSetDlgService::OnBnClickedButtonDel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int sel = listService.GetCurSel();
	if( sel == LB_ERR ){
		return ;
	}
	if( MessageBox(L"削除を行うと、再度チャンネルスキャンを行うまで項目が表示されなくなります。\r\nよろしいですか？",L"", MB_OKCANCEL) == IDOK ){
		CH_DATA4* chSet = (CH_DATA4*)listService.GetItemDataPtr(sel);

		CString text = L"";
		combBon.GetWindowText(text);

		wstring key = text.GetBuffer(0);
		map<wstring, CH_SET_INFO*>::iterator itr;
		itr = chList.find(key);
		if( itr != chList.end()){
			itr->second->chSet.DelChService(chSet->space, chSet->ch, chSet->serviceID);
			ReloadList();
		}
	}
}


void CSetDlgService::OnLbnSelchangeListService()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int sel = listService.GetCurSel();
	if( sel == LB_ERR ){
		return ;
	}
	CH_DATA4* chSet = (CH_DATA4*)listService.GetItemDataPtr(sel);
	CString info = L"";
	info.Format(L"space: %d ch: %d (%s)\r\nOriginalNetworkID: %d(0x%04X)\r\nTransportStreamID: %d(0x%04X)\r\nServiceID: %d(0x%04X)\r\nServiceType: %d(0x%02X)\r\n",
		chSet->space,
		chSet->ch,
		chSet->chName.c_str(),
		chSet->originalNetworkID,
		chSet->originalNetworkID,
		chSet->transportStreamID,
		chSet->transportStreamID,
		chSet->serviceID,
		chSet->serviceID,
		chSet->serviceType,
		chSet->serviceType
		);
	editCh.SetWindowText(info);

}
