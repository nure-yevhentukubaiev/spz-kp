#pragma once
#include "stdafx.h"

extern INT g_argc;
extern TCHAR **g_argv;
extern LPTSTR lpszAppName;

extern WORD g_SMBIOSVersion;

VOID app_atstart(VOID);

VOID app_atexit(VOID);

VOID app_error(LPCTSTR lpszErrorDesc);