/*
 * smbios_raw.h
 * Functionality for retrieving raw SMBIOS table
 */

#pragma once
#include "stdafx.h"

#define MKSMBIOSVERSION(major, minor) (WORD)((major << 8) | (minor))

typedef struct tagRawSMBIOSData
{
	BYTE    Used20CallingMethod;
	BYTE    SMBIOSMajorVersion;
	BYTE    SMBIOSMinorVersion;
	BYTE    DmiRevision;
	DWORD   Length;
	BYTE    SMBIOSTableData[];
} RawSMBIOSData;

VOID OutSMBIOSVersion(CONST RawSMBIOSData *smbios);

BOOL GetRawSMBIOS(RawSMBIOSData **smbios);