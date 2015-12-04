// clipregjump.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

#include <sstream>
#include <iostream>
#include <vector>

#include "../MyUtility/IsFileExists.h"
#include "../MyUtility/GetClipboardText.h"
#include "../MyUtility/GetOpenFile.h"
#include "../MyUtility/I18N.h"
using namespace Ambiesoft;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow )
{
	i18nInitLangmap();

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
		CGetOpenFileFilter filter;
		filter.AddFilter(_T("regjump.exe"),_T("regjump.exe"), false);
		filter.AddFilter(I18N(_T("Application")),_T("*.exe;*.com"));
		filter.AddFilter(I18N(_T("All Files")), _T("*.*"));
		tstring fullpath;
		if(!GetOpenFile(NULL,
			filter,
			NULL,
			I18N(_T("Specify regjump.exe")),
			&fullpath))
		{
			return -1;
		}

		if(!WritePrivateProfileString(
			_T("option"),
			_T("regjumppath"),
			fullpath.c_str(),
			szIni))
		{
			MessageBox(NULL, I18N(_T("Failed to save .ini")),
				_T("clipregjump"), MB_ICONERROR);
			return -1;
		}

		lstrcpy(szRegjumpPath, fullpath.c_str());
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


	//vector<tstring> lines;
	//wistringstream f(strClip);
	//wstring line;    
	//while (std::getline(f, line)) {
	//	lines.push_back(line);
	//}

	if(strClip[0] != L'"')
		strClip = L'"' + strClip + L'"';

	ShellExecute(NULL,NULL,szRegjumpPath,
		strClip.c_str(), NULL, SW_SHOW);


	return 0;
}



