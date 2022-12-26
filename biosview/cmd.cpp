#include "cmd.h"
#include "stdafx.h"
#include "app.h"

static VOID cmd_help(VOID)
{
	std::wcout << 
		_T("Usage:") << _T("\n")
		<< _T("\t") << (LPTSTR)(g_argv[0])
		<< _T(" [-? | -h | -r | -s | -x | -w]") << _T("\n")
		<< _T("Options:") << _T("\n")
		<< _T("\t-?, -h   Show this help") << _T("\n")
		<< _T("\t-r       Output raw SMBIOS table") << _T("\n")
		<< _T("\t-s       Show structured SMBIOS view") << _T("\n")
		<< _T("\t-x       Show raw SMBIOS table view ") << _T("\n")
		<< _T("\t-w       Show Win32_BIOS WMI class view") << _T("\n")
		<< _T("-- \n");
	return;
}

static VOID cmd_get_from_wmi(VOID)
{
	return;
}

static VOID cmd_get_raw(VOID)
{
	return;
}

static VOID cmd_get_hex(VOID)
{
	return;
}

static VOID cmd_get_structured(VOID)
{
	return;
}

INT cmd_main(VOID)
{
	return 0;
}