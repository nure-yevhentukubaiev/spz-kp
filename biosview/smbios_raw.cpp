#include "stdafx.h"
#include "smbios_raw.h"

BOOL GetRawSMBIOS(RawSMBIOSData *smbios)
{
	BOOL bRet = FALSE;

	bRet = TRUE;
	std::wcout << _T(__FUNCTION__) << _T(" success") << _T("\n");
	done:
	return bRet;
}

BOOL OutRawSMBIOS(RawSMBIOSData *smbios)
{
	BOOL bRet = TRUE;
	
	return bRet;
}