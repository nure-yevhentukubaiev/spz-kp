#include "cmd.h"
#include "stdafx.h"
#include "app.h"
#include "smbios_raw.h"
#include "smbios_wmi.h"
#include "smbios_struct.h"

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
	BOOL bRet = FALSE;
	if (!GetRawSMBIOS(&smbios)) {
		goto done;
	}

	/* Finally, write to stdout */
	std::cout.write((CONST CCHAR *)(smbios), smbios->Length);

	
	bRet = TRUE;
	done:
	HeapFree(GetProcessHeap(), 0, smbios);
	return bRet;
}

static VOID cmd_get_structured(VOID)
{
	RawSMBIOSData *smbios;
	GetRawSMBIOS(&smbios);
	
	OutSMBIOSVersion(smbios);

	SMBIOS_Type0 a; 
	a.Table = (SMBIOS_Type0_Raw *)smbios->SMBIOSTableData;
	GetSMBIOSStrings((SMBIOS_BaseStruct *)&a);
	
	OutSMBIOSStruct_Type0(&a);

	HeapFree(GetProcessHeap(), 0, a.Strings);
	HeapFree(GetProcessHeap(), 0, smbios);
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
			cmd_get_structured();
			return 0;
		case _T('w'):
			cmd_get_from_wmi();
			return 0;
		default:
			app_error(_T("Invalid flag."));
			cmd_help();
			return 2;
		}
	}
	return 0;
}