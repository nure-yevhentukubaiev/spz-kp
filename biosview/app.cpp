#include "stdafx.h"
#include "app.h"

INT g_argc = 0;
TCHAR **g_argv = NULL;

VOID app_atstart(VOID)
{
	atexit(app_atexit);
	return;
}

VOID app_atexit(VOID)
{
	return;
}

VOID app_error(LPCTSTR lpszErrorAddDesc)
{
	DWORD dwErr = GetLastError();
	LPTSTR lpszErrorDesc = NULL;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER
		| FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwErr,
		0, (LPTSTR)&lpszErrorDesc, 0,
		NULL
	);
	
	if (dwErr)
		std::wcerr << _T("Windows error: ") << lpszErrorDesc << _T("\n");
	if (lpszErrorAddDesc)
		std::wcerr << _T("Error: ") << lpszErrorAddDesc << _T("\n");

	LocalFree(lpszErrorDesc);
	return;
}