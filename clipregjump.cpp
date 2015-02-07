// clipregjump.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "../MyUtility/IsFileExists.h"
#include "../MyUtility/GetClipboardText.h"
#include "../MyUtility/I18N.h"
using namespace Ambiesoft;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow )
{
	initLangmap();

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
	if(!GetClipboardText(NULL, strClip))
	{
		MessageBox(NULL, I18N(_T("could not get clipboard text")),
			_T("clipregjump"), MB_ICONERROR);
		return -1;
	}

	if(strClip.empty())
	{
		MessageBox(NULL, I18N(_T("Clipboard text is empty")),
			_T("clipregjump"), MB_ICONERROR);
		return -1;
	}

	if(strClip[0] != L'"')
		strClip = L'"' + strClip + L'"';

	ShellExecute(NULL,NULL,szRegjumpPath,
		strClip.c_str(), NULL, SW_SHOW);


	return 0;
}



