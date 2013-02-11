#pragma once
#include "afxwin.h"
#include <map>
using namespace std;

class CCmdLineUtil :
	public CCommandLineInfo
{
public:
	CCmdLineUtil(void);
	~CCmdLineUtil(void);

	void ParseParam( const TCHAR* pszParam, BOOL bFlag, BOOL bLast );
	
	map<CString, CString> m_CmdList;

protected:
	CString m_strOpt;
	CString m_strOpt2;
};
