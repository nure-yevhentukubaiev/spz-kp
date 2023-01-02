#include "stdafx.h"
#include "smbios_raw.h"
#include "app.h"

VOID OutSMBIOSVersion(CONST RawSMBIOSData *smbios)
{
	std::wcout << _T("SMBIOS Version: ")
		<< smbios->SMBIOSMajorVersion << _T(".")
		<< smbios->SMBIOSMinorVersion << _T(".")
		<< smbios->DmiRevision << _T("\n");
	return;
}

BOOL GetRawSMBIOS(RawSMBIOSData **smbios)
{
	/*
	* Retrieving SMBIOS table needed buffer size, if any table is present
	*/
	DWORD dwSMBIOSSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);
	BOOL bRet = FALSE;
	if (dwSMBIOSSize == 0) {
		app_error(_T("Seems like SMBIOS is not supported on this system"));
		goto done;
	}

	*smbios = (RawSMBIOSData *)HeapAlloc(
		GetProcessHeap(),
		0,
		dwSMBIOSSize
	);

	/*
	* Checking if buffer is sufficient enough &
	* retrieving SMBIOS table
	*/
	if (dwSMBIOSSize != GetSystemFirmwareTable('RSMB', 0, *smbios, dwSMBIOSSize)) {
		app_error(NULL);
		goto done;
	}

	g_SMBIOSVersion = MKSMBIOSVERSION(
		(*smbios)->SMBIOSMajorVersion,
		(*smbios)->SMBIOSMinorVersion
	);
	bRet = TRUE;
	done:
	return bRet;
}