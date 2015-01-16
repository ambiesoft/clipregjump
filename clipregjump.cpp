// clipregjump.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	TCHAR szT[MAX_PATH];
	GetModuleFileName(NULL,szT,MAX_PATH);
	*_tcsrchr(szT,_T('\\')=0;
	lstrcat(szT, _T("\\clipregjump.ini"));

	TCHAR szRegjumpPath[MAX_PATH];
	if(GetPrivateProfileString(
		_T("option"),
		_T("regjumppath"),
		szRegjumpPath,
		_T(""),
		szT) && IsFileExists

	return 0;
}



