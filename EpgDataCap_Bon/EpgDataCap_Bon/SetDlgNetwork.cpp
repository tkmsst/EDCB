// SetDlgNetwork.cpp : 実装ファイル
//

#include "stdafx.h"
#include "EpgDataCap_Bon.h"
#include "SetDlgNetwork.h"
#include "afxdialogex.h"

#include "../../Common/PathUtil.h"
#include "../../Common/StringUtil.h"

// CSetDlgNetwork ダイアログ

IMPLEMENT_DYNAMIC(CSetDlgNetwork, CDialog)

CSetDlgNetwork::CSetDlgNetwork(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlgNetwork::IDD, pParent)
	, udpPort(0)
	, udpWaitSec(0)
	, udpWaitPacket(0)
	, tcpPort(0)
{

}

CSetDlgNetwork::~CSetDlgNetwork()
{
}

void CSetDlgNetwork::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IP_UDP, udpList);
	DDX_Control(pDX, IDC_IPADDRESS_UDP, udpIP);
	DDX_Text(pDX, IDC_EDIT_PORT_UDP, udpPort);
	DDX_Control(pDX, IDC_CHECK_BROADCAST, udpBroadcast);
	DDX_Text(pDX, IDC_EDIT_WAIT_SEC, udpWaitSec);
	DDX_Text(pDX, IDC_EDIT_WAIT_PACKET, udpWaitPacket);
	DDX_Control(pDX, IDC_LIST_IP_TCP, tcpList);
	DDX_Control(pDX, IDC_IPADDRESS_TCP, tcpIP);
	DDX_Text(pDX, IDC_EDIT_PORT_TCP, tcpPort);
}


BEGIN_MESSAGE_MAP(CSetDlgNetwork, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_UDP, &CSetDlgNetwork::OnBnClickedButtonAddUdp)
	ON_BN_CLICKED(IDC_BUTTON_DEL_UDP, &CSetDlgNetwork::OnBnClickedButtonDelUdp)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TCP, &CSetDlgNetwork::OnBnClickedButtonAddTcp)
	ON_BN_CLICKED(IDC_BUTTON_DEL_TCP, &CSetDlgNetwork::OnBnClickedButtonDelTcp)
END_MESSAGE_MAP()


// CSetDlgNetwork メッセージ ハンドラー


BOOL CSetDlgNetwork::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	udpIP.SetAddress( GetPrivateProfileInt( L"SET", L"UDPIP", 2130706433, appIniPath ));
	udpPort = GetPrivateProfileInt( L"SET", L"UDPPort", 1234, appIniPath );
	udpWaitSec = GetPrivateProfileInt( L"SET", L"UDPWait", 4, appIniPath );
	udpWaitPacket = GetPrivateProfileInt( L"SET", L"UDPPacket", 128, appIniPath );

	int udpCount = GetPrivateProfileInt( L"SET_UDP", L"Count", 0, appIniPath );
	for( int i = 0; i < udpCount; i++ ){
		NW_SEND_INFO item;

		CString key = L"";
		key.Format(L"IP%d",i);
		item.ip = GetPrivateProfileInt( L"SET_UDP", key.GetBuffer(0), 2130706433, appIniPath );
		key.Format(L"Port%d",i);
		item.port = GetPrivateProfileInt( L"SET_UDP", key.GetBuffer(0), 1234, appIniPath );
		Format(item.ipString, L"%d.%d.%d.%d",
			(item.ip&0xFF000000)>>24,
			(item.ip&0x00FF0000)>>16,
			(item.ip&0x0000FF00)>>8,
			(item.ip&0x000000FF) );
		key.Format(L"BroadCast%d",i);
		item.broadcastFlag = GetPrivateProfileInt( L"SET_UDP", key.GetBuffer(0), 0, appIniPath );

		udpSendList.push_back(item);

		CString add = L"";
		add.Format(L"%s:%d",item.ipString.c_str(), item.port);
		if( item.broadcastFlag == TRUE ){
			add+= L" ブロードキャスト";
		}
		int index = udpList.AddString(add);
		udpList.SetItemData(index, i);
	}


	tcpIP.SetAddress( GetPrivateProfileInt( L"SET", L"TCPIP", 2130706433, appIniPath ));
	tcpPort = GetPrivateProfileInt( L"SET", L"TCPPort", 2230, appIniPath );

	int tcpCount = GetPrivateProfileInt( L"SET_TCP", L"Count", 0, appIniPath );
	for( int i = 0; i < tcpCount; i++ ){
		NW_SEND_INFO item;

		CString key = L"";
		key.Format(L"IP%d",i);
		item.ip = GetPrivateProfileInt( L"SET_TCP", key.GetBuffer(0), 2130706433, appIniPath );
		key.Format(L"Port%d",i);
		item.port = GetPrivateProfileInt( L"SET_TCP", key.GetBuffer(0), 2230, appIniPath );
		Format(item.ipString, L"%d.%d.%d.%d",
			(item.ip&0xFF000000)>>24,
			(item.ip&0x00FF0000)>>16,
			(item.ip&0x0000FF00)>>8,
			(item.ip&0x000000FF) );
		item.broadcastFlag = 0;

		tcpSendList.push_back(item);

		CString add = L"";
		add.Format(L"%s:%d",item.ipString.c_str(), item.port);
		int index = tcpList.AddString(add);
		tcpList.SetItemData(index, i);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CSetDlgNetwork::SaveIni(void)
{
	UpdateData(TRUE);

	CString val = L"";
	DWORD ip = 0;
	udpIP.GetAddress(ip);
	val.Format(L"%d",ip);
	WritePrivateProfileString( L"SET", L"UDPIP", val.GetBuffer(0), appIniPath );
	val.Format( L"%d", udpPort );
	WritePrivateProfileString(L"SET", L"UDPPort", val.GetBuffer(0), appIniPath);
	val.Format( L"%d", udpWaitSec );
	WritePrivateProfileString(L"SET", L"UDPWait", val.GetBuffer(0), appIniPath);
	val.Format( L"%d", udpWaitPacket );
	WritePrivateProfileString(L"SET", L"UDPPacket", val.GetBuffer(0), appIniPath);

	val.Format( L"%d", udpSendList.size() );
	WritePrivateProfileString(L"SET_UDP", L"Count", val.GetBuffer(0), appIniPath);
	for( int i = 0; i < (int)udpSendList.size(); i++ ){
		CString key = L"";
		key.Format(L"IP%d",i);
		val.Format(L"%d",udpSendList[i].ip);
		WritePrivateProfileString( L"SET_UDP", key.GetBuffer(0), val.GetBuffer(0), appIniPath );
		key.Format(L"Port%d",i);
		val.Format(L"%d",udpSendList[i].port);
		WritePrivateProfileString( L"SET_UDP", key.GetBuffer(0), val.GetBuffer(0), appIniPath );
		key.Format(L"BroadCast%d",i);
		val.Format(L"%d",udpSendList[i].broadcastFlag);
		WritePrivateProfileString( L"SET_UDP", key.GetBuffer(0), val.GetBuffer(0), appIniPath );
	}

	tcpIP.GetAddress(ip);
	val.Format(L"%d",ip);
	WritePrivateProfileString( L"SET", L"TCPIP", val.GetBuffer(0), appIniPath );
	val.Format( L"%d", tcpPort );
	WritePrivateProfileString(L"SET", L"TCPPort", val.GetBuffer(0), appIniPath);

	val.Format( L"%d", tcpSendList.size() );
	WritePrivateProfileString(L"SET_TCP", L"Count", val.GetBuffer(0), appIniPath);
	for( int i = 0; i < (int)tcpSendList.size(); i++ ){
		CString key = L"";
		key.Format(L"IP%d",i);
		val.Format(L"%d",tcpSendList[i].ip);
		WritePrivateProfileString( L"SET_TCP", key.GetBuffer(0), val.GetBuffer(0), appIniPath );
		key.Format(L"Port%d",i);
		val.Format(L"%d",tcpSendList[i].port);
		WritePrivateProfileString( L"SET_TCP", key.GetBuffer(0), val.GetBuffer(0), appIniPath );
	}

	UpdateData(FALSE);
}

BOOL CSetDlgNetwork::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	if( pMsg->message == WM_KEYDOWN ){
		if( pMsg->wParam  == VK_RETURN || pMsg->wParam  == VK_ESCAPE ){
			return FALSE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CSetDlgNetwork::OnBnClickedButtonAddUdp()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(TRUE);
	DWORD ip = 0;
	udpIP.GetAddress(ip);

	NW_SEND_INFO item;
	item.ip = ip;
	item.port = udpPort;
	Format(item.ipString, L"%d.%d.%d.%d",
		(item.ip&0xFF000000)>>24,
		(item.ip&0x00FF0000)>>16,
		(item.ip&0x0000FF00)>>8,
		(item.ip&0x000000FF) );

	CString add = L"";
	add.Format(L"%s:%d",item.ipString.c_str(), item.port);
	if( udpBroadcast.GetCheck() == TRUE ){
		add+= L" ブロードキャスト";
		item.broadcastFlag = TRUE;
	}else{
		item.broadcastFlag = FALSE;
	}

	for( int i=0; i<udpList.GetCount(); i++ ){
		CString buff=L"";
		udpList.GetText(i,buff);
		if(buff.CompareNoCase(add) == 0 ){
			return ;
		}
	}
	int index = udpList.AddString(add);
	udpList.SetItemData(index, (int)udpSendList.size());
	udpSendList.push_back(item);
}


void CSetDlgNetwork::OnBnClickedButtonDelUdp()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int sel = udpList.GetCurSel();
	if( sel != LB_ERR ){
		int index = (int)udpList.GetItemData(sel);

		vector<NW_SEND_INFO>::iterator itr;
		itr = udpSendList.begin();
		advance(itr, index);
		udpSendList.erase(itr);

		udpList.ResetContent();

		for( int i=0; i<(int)udpSendList.size(); i++ ){
			CString add = L"";
			add.Format(L"%s:%d",udpSendList[i].ipString.c_str(), udpSendList[i].port);
			if( udpSendList[i].broadcastFlag == TRUE ){
				add+= L" ブロードキャスト";
			}
			int index = udpList.AddString(add);
			udpList.SetItemData(index, i);
		}
	}
}


void CSetDlgNetwork::OnBnClickedButtonAddTcp()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	UpdateData(TRUE);
	DWORD ip = 0;
	tcpIP.GetAddress(ip);

	NW_SEND_INFO item;
	item.ip = ip;
	item.port = tcpPort;
	Format(item.ipString, L"%d.%d.%d.%d",
		(item.ip&0xFF000000)>>24,
		(item.ip&0x00FF0000)>>16,
		(item.ip&0x0000FF00)>>8,
		(item.ip&0x000000FF) );

	CString add = L"";
	add.Format(L"%s:%d",item.ipString.c_str(), item.port);
	item.broadcastFlag = FALSE;

	for( int i=0; i<tcpList.GetCount(); i++ ){
		CString buff=L"";
		tcpList.GetText(i,buff);
		if(buff.CompareNoCase(add) == 0 ){
			return ;
		}
	}
	int index = tcpList.AddString(add);
	tcpList.SetItemData(index, (int)tcpSendList.size());
	tcpSendList.push_back(item);
}


void CSetDlgNetwork::OnBnClickedButtonDelTcp()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int sel = tcpList.GetCurSel();
	if( sel != LB_ERR ){
		int index = (int)tcpList.GetItemData(sel);

		vector<NW_SEND_INFO>::iterator itr;
		itr = tcpSendList.begin();
		advance(itr, index);
		tcpSendList.erase(itr);

		tcpList.ResetContent();

		for( int i=0; i<(int)tcpSendList.size(); i++ ){
			CString add = L"";
			add.Format(L"%s:%d",tcpSendList[i].ipString.c_str(), tcpSendList[i].port);
			int index = tcpList.AddString(add);
			tcpList.SetItemData(index, i);
		}
	}
}
