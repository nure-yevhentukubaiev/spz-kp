/*
* smbios_defs.h
* Structure definitions from SMBIOS standard
*/
#pragma once
#include "stdafx.h"

/*
 * Common for SMBIOS table structures header
 * - Type - Type of structure
 * - Length - Length of the formatted data (not including strings)
 * - Handle -
 */
typedef struct tagSMBIOS_Header {
	BYTE Type   : 8;
	BYTE Length : 8;
	WORD Handle : 16;
} SMBIOS_Header;

typedef struct tagBIT_DESC {
	LPCTSTR desc;
	UINT val;
} BIT_DESC;

typedef BYTE SMBIOS_BaseStruct_Val;

typedef struct tagSMBIOS_BaseStruct_Raw {
	SMBIOS_Header Header;
	SMBIOS_BaseStruct_Val Data[];
} SMBIOS_BaseStruct_Raw;

typedef struct tagSMBIOS_BaseStruct {
	SMBIOS_BaseStruct_Raw *Table;
	LPCSTR *Strings;
} SMBIOS_BaseStruct;

typedef struct tagSMBIOS_Type0_Raw {
	/* 2.0+ */ SMBIOS_Header Header;
	/* 2.0+ */ BYTE VendorStr : 8;
	/* 2.0+ */ BYTE BIOSVersionStr : 8;
	/* 2.0+ */ WORD BIOSStartAddressSegment : 16;
	/* 2.0+ */ BYTE BIOSReleaseDateStr : 8;
	/* 2.0+ */ BYTE BIOSRomSize : 8;
	/* 2.0+ */ struct _BIOSCharacheristics {
		BYTE /* Reserved */                    : 1;
		BYTE /* Reserved */                    : 1;
		BYTE Unknown2                          : 1;
		BYTE BIOSCharacteristicsNotSupported   : 1;
		BYTE ISASupported                      : 1;
		BYTE MCASupported                      : 1;
		BYTE EISASupported                     : 1;
		BYTE PCISupported                      : 1;
		BYTE PCMCIASupported                   : 1;
		BYTE PnPSupported                      : 1;
		BYTE APMSupported                      : 1;
		BYTE BIOSUpgradeable                   : 1;
		BYTE BIOSShadowingAllowed              : 1;
		BYTE VL_VESASupported                  : 1;
		BYTE ECSDSupported                     : 1;
		BYTE CDBootSupported                   : 1;
		BYTE SelectableBootSupported           : 1;
		BYTE BIOSRomSocketed                   : 1;
		BYTE PCMCIABootSupported               : 1;
		BYTE EDDSpecSupported                  : 1;
		BYTE Int13_NEC9800Supported            : 1;
		BYTE Int13_ToshibaSupported            : 1;
		BYTE Int13_Floppy360kbSupported        : 1;
		BYTE Int13_Floppy1p2mbSupported        : 1;
		BYTE Int13_Floppy720kbSupported        : 1;
		BYTE Int13_Floppy2p8mbSupported        : 1;
		BYTE Int5Supported                     : 1;
		BYTE Int9Supported                     : 1;
		BYTE Int14Supported                    : 1;
		BYTE Int17Supported                    : 1;
		BYTE Int10Supported                    : 1;
		BYTE NEC_PC98                          : 1;
		WORD /* Reserved_for_BIOS_vendor */    : 16;
		WORD /* Reserved_for_system_vendor */  : 16;
	} BIOSCharacteristics;
	/* 2.4+ */ struct _BIOSCharacheristicsEx {
		/* 2.1+ */ struct _Byte1 {
			BYTE ACPISupported         : 1;
			BYTE USBLegacySupported    : 1;
			BYTE AGPSupported          : 1;
			BYTE I20BootSupported      : 1;
			BYTE LS120BootSupported    : 1;
			BYTE ATAPIZIPBootSupported : 1;
			BYTE _1394BootSupported    : 1;
			BYTE SmartBatterySupported : 1;
		} Byte1;
		/* 2.3+ */ struct _Byte2 {
			BYTE BIOSBootSpecSupported      : 1;
			BYTE FKINSBootSupported         : 1;
			BYTE TCDEnabled                 : 1;
			BYTE UEFISupported              : 1;
			BYTE IsVirtualMachine           : 1;
			BYTE ManufacturingModeSupported : 1;
			BYTE ManufacturingModeEnabled   : 1;
			BYTE /* Reserved */             : 1;
		} Byte2;
	} BIOSCharacteristicsEx;
	/* 2.4+ */ BYTE SystemBIOSMajorRelease  : 8;
	/* 2.4+ */ BYTE SystemBIOSMinorRelease  : 8;
	/* 2.4+ */ BYTE EmbeddedConMajorRelease : 8;
	/* 2.4+ */ BYTE EmbeddedConMinorRelease : 8;
	/* 3.1+ */ struct _BIOSRomSizeEx {
		WORD Size : 14;
		BYTE Unit : 2;
	} BIOSRomSizeEx;
} SMBIOS_Type0_Raw;

typedef struct tagSMBIOS_Type0 {
	SMBIOS_Type0_Raw *Table;
	LPCSTR *Strings;
} SMBIOS_Type0;

BOOL GetSMBIOSStrings(SMBIOS_BaseStruct *base);

VOID OutSMBIOSStruct_Type0(CONST SMBIOS_Type0 *s);