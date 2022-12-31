#include "cmd.h"
#include "stdafx.h"
#include "app.h"
#include "smbios_raw.h"
#include "smbios_wmi.h"

static VOID cmd_help(VOID)
{
	std::wcout << 
		_T("Usage:") << _T("\n")
		<< _T("\t") << (LPTSTR)(g_argv[0])
		<< _T(" [-? | -h | -r | -s | -w]") << _T("\n")
		<< _T("Options:") << _T("\n")
		<< _T("\t-?, -h   Show this help") << _T("\n")
		<< _T("\t-r       Output raw SMBIOS table") << _T("\n")
		<< _T("\t-s       Show structured SMBIOS view") << _T("\n")
		<< _T("\t-w       Show Win32_BIOS WMI class view") << _T("\n")
		<< _T("\0");
	return;
}

static VOID cmd_get_from_wmi(VOID)
{
	CoInit();
	WMIConnect();
	GetSMBIOSFromWMI();
	WMIClose();
	return;
}

static BOOL cmd_get_raw(VOID)
{
	RawSMBIOSData *smbios;
	/*
	 * Retrieving SMBIOS table needed buffer size, if any table is present
	 */
	DWORD dwSMBIOSSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);
	BOOL bRet = FALSE;
	if (dwSMBIOSSize == 0) {
		app_error(_T("Seems like SMBIOS is not supported on this system"));
		goto done;
	}

	smbios = (RawSMBIOSData *)HeapAlloc(
		GetProcessHeap(),
		0,
		dwSMBIOSSize
	);

	/*
	 * Checking if buffer is sufficient enough &
	 * retrieving SMBIOS table
	 */
	if (dwSMBIOSSize != GetSystemFirmwareTable('RSMB', 0, smbios, dwSMBIOSSize)) {
		app_error(NULL);
		goto done;
	}

	std::cout.flush();
	/* Finally, write to stdout */
	std::cout.write((CONST CCHAR *)(smbios), smbios->Length);

	HeapFree(GetProcessHeap(), 0, smbios);
	done:
	return bRet;
}

static VOID cmd_get_structured(VOID)
{
	
	return;
}

INT cmd_main(VOID)
{
	if (g_argc == 1) {
		app_error(_T("Specify at least one flag."));
		cmd_help();
		return 1;
	}
	for (INT i = 1; i < g_argc; ++i) {
		switch ((g_argv[i])[1]) {
		case _T('h'):
		case _T('?'):
			cmd_help();
			return 0;
		case _T('r'):
			cmd_get_raw();
			return 0;
		case _T('s'):
			return 0;
		case _T('w'):
			cmd_get_from_wmi();
			return 0;
		default:
			return 2;
		}
	}
	return 0;
}