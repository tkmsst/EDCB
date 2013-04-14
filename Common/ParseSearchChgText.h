#ifndef __PARSE_SEARCH_CHG_TEXT_H__
#define __PARSE_SEARCH_CHG_TEXT_H__

#include "StructDef.h"

////////////////////////////////////////////////////////////////////////////
//文字変換情報ファイルの「SearchChg.txt」の読み込みを行うためのクラス
//排他制御などは行っていないため、複数スレッドからのアクセスは上位層で排他制
//御を行うこと
////////////////////////////////////////////////////////////////////////////
class CParseSearchChgText
{
public:
	CParseSearchChgText(void);
	~CParseSearchChgText(void);

	//SearchChg.txtの読み込みを行う
	//引数：
	// file_path	SearchChg.txtのフルパス
	//戻り値：
	// TRUE（成功）、FALSE（失敗）
	BOOL ParseReserveText(LPCWSTR filePath);
	//読み込んだ変換情報を元に文字列の変換を行う
	//引数：
	// chgText		変換を行う文字列
	//戻り値：
	void ChgText(wstring& chgText);

protected:
	typedef struct _CHG_INFO{
		wstring oldText;	//変換対象の文字列
		wstring newText;	//変換する文字列
	} CHG_INFO;
	vector<CHG_INFO> chgKey;

protected:
	BOOL Parse1Line(string parseLine, wstring& oldText, wstring& newText);
};

#endif
