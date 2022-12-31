/*
 * smbios_raw.h
 * Functionality for retrieving raw SMBIOS table
 */

#pragma once
#include "stdafx.h"

typedef struct tagRawSMBIOSData
{
	BYTE    Used20CallingMethod;
	BYTE    SMBIOSMajorVersion;
	BYTE    SMBIOSMinorVersion;
	BYTE    DmiRevision;
	DWORD   Length;
	BYTE    SMBIOSTableData[];
} RawSMBIOSData;