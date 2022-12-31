#include "stdafx.h"
#include "smbios_raw.h"

VOID OutSMBIOSVersion(RawSMBIOSData *smbios)
{
	std::wcout << _T("SMBIOS Version: ")
		<< smbios->SMBIOSMajorVersion << _T(".")
		<< smbios->SMBIOSMinorVersion << _T(".")
		<< smbios->DmiRevision << _T("\n");
	return;
}