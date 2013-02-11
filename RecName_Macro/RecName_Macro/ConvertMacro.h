#pragma once

#include "RecName_PlugIn.h"

#include <string>
using namespace std;

class CConvertMacro
{
public:
	CConvertMacro(void);
	~CConvertMacro(void);

	BOOL Convert(wstring macro, PLUGIN_RESERVE_INFO* info, wstring& convert);
};

