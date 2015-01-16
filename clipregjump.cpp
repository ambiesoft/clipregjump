// clipregjump.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "../MyUtility/IsFileExists.h"
#include "../MyUtility/GetClipboardTexts.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	TCHAR szFolder[MAX_PATH];
	TCHAR szIni[MAX_PATH];
	GetModuleFileName(NULL,szFolder,MAX_PATH);
	*_tcsrchr(szFolder,_T('\\'))=0;

	lstrcpy(szIni, szFolder);
	lstrcat(szIni, _T("\\clipregjump.ini"));

	TCHAR szRegjumpPath[MAX_PATH];
	GetPrivateProfileString(
		_T("option"),
		_T("regjumppath"),
		_T(""),
		szRegjumpPath,
		MAX_PATH,
		szIni);

	if(!IsFileExists(szRegjumpPath))
	{
		lstrcpy(szRegjumpPath, szFolder);
		lstrcat(szRegjumpPath, _T("\\regjump.exe"));
	}

	if(!IsFileExists(szRegjumpPath))
	{
		MessageBox(NULL, _T("regjump.exe not found"),
			_T("clipregjump"), MB_ICONERROR);
		return -1;
	}

	tstring strClip;
	if(!GetClipboardTexts(NULL, strClip))
	{
		MessageBox(NULL, _T("could not get clipboard text"),
			_T("clipregjump"), MB_ICONERROR);
		return -1;
	}

	ShellExecute(NULL,NULL,szRegjumpPath,
		strClip.c_str(), NULL, SW_SHOW);


	return 0;
}



