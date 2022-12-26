#include "stdafx.h"
#include "app.h"

INT g_argc = 0;
TCHAR **g_argv = NULL;

LPTSTR lpszAppName = NULL;

VOID app_atstart(VOID)
{
	lpszAppName = (LPTSTR)HeapAlloc(
		GetProcessHeap(),
		0,
		sizeof(TCHAR) * (lstrlen(g_argv[0]) + 1)
	);
	lstrcpy(lpszAppName, g_argv[0]);
	atexit(app_atexit);
	return;
}

VOID app_atexit(VOID)
{
	HeapFree(GetProcessHeap(), 0, lpszAppName);
	return;
}