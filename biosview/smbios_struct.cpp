#include "stdafx.h"
#include "smbios_struct.h"
#include "smbios_raw.h"
#include "app.h"

BOOL GetSMBIOSStrings(SMBIOS_BaseStruct *base)
{
	LPCSTR b = (LPCSTR)((BYTE *)(base->Table) + base->Table->Header.Length);
	DWORD num = 0;
	for (b; strlen(b); b += strlen(b) + 1)
		num++;

	b = (LPCSTR)((BYTE *)(base->Table) + base->Table->Header.Length);
	base->Strings = (LPCSTR *)HeapAlloc(GetProcessHeap(), 0, sizeof(LPCSTR) * num);
	for (DWORD i = 0; i < num; ++i, b += strlen(b) + 1) {
		base->Strings[i] = b;
	}

	return TRUE;
}

VOID OutSMBIOSStruct_Type0(CONST SMBIOS_Type0 *s)
{
	CONST SMBIOS_Type0_Raw *table = s->Table;

	if (g_SMBIOSVersion < MKSMBIOSVERSION(2,0)) {
		app_error(_T("Seems like SMBIOS is too old on this system"));
		return;
	}

	std::wcout << _T("Type: ") << s->Table->Header.Type << _T("\n");
	std::wcout << _T("Handle: ") << std::hex << s->Table->Header.Handle << _T("\n");

	std::wcout << _T("BIOS Vendor: ");
	if (table->VendorStr) {
		 std::wcout << s->Strings[table->VendorStr-1];
	} else {
		std::wcout << _T("No data");
	}
	std::wcout << _T("\n");

	std::wcout << _T("BIOS Version: ");
	if (table->BIOSVersionStr) {
		std::wcout << s->Strings[table->BIOSVersionStr-1];
	} else {
		std::wcout << _T("No data");
	}
	std::wcout << _T("\n");

	std::wcout << _T("BIOS Start Address: ");
	if (table->BIOSStartAddressSegment) {
		std::wcout << table->BIOSStartAddressSegment;
	} else {
		std::wcout << _T("Not appllicable (UEFI system)");
	}
	std::wcout << _T("\n");
	
	std::wcout << _T("BIOS Release Date: ");
	if (table->BIOSReleaseDateStr) {
		std::wcout << s->Strings[table->BIOSReleaseDateStr-1];
	} else {
		std::wcout << _T("No data");
	}
	std::wcout << _T("\n");

	std::wcout << _T("BIOS ROM Size: ");
	if (table->BIOSRomSize < (BYTE)0xFF) {
		std::wcout << (table->BIOSRomSize + 1) * 64 << _T(" KB ");
	} else {
		std::wcout << table->BIOSRomSizeEx.Size;
		switch (table->BIOSRomSizeEx.Unit) {
		case 0x00:
			std::wcout << _T(" MB ");
			break;
		case 0x01:
			std::wcout << _T(" GB ");
			break;
		default:
			std::wcout << _T(" (unknown) ");
			break;
		}
		std::wcout << _T("(extended)");
	}
	std::wcout << _T("\n");

	std::wcout << _T("BIOS Characteristics: ");
	if (table->BIOSCharacteristics.BIOSCharacteristicsNotSupported) {
		std::wcout << _T("Not supported");
	} else {
		std::wcout << _T("\n");
		#define chars table->BIOSCharacteristics
		BIT_DESC flags[] = {
			{_T("ISA is supported: "), chars.ISASupported},
			{_T("MCA is supported: "), chars.MCASupported},
			{_T("EISA is supported: "), chars.EISASupported},
			{_T("PCI is supported: "), chars.PCISupported},
			{_T("PCMCIA is supported: "), chars.PCMCIASupported},
			{_T("PnP is supported: "), chars.PnPSupported},
			{_T("APM is supported: "), chars.APMSupported},
			{_T("BIOS is upgradeable (Flash): "), chars.BIOSUpgradeable},
			{_T("BIOS shadowing is allowed: "), chars.BIOSShadowingAllowed},
			{_T("VL-VESA is supported: "), chars.VL_VESASupported},
			{_T("ESCD is supported: "), chars.ECSDSupported},
			{_T("Boot from CD is supported: "), chars.ISASupported},
			{_T("BIOS ROM is socketed: "), chars.BIOSRomSocketed},
			{_T("Boot from PCMCIA is supported: "), chars.PCMCIABootSupported},
			{_T("EDD specification is supported: "), chars.EDDSpecSupported},
			{_T("Int 13h - Japanese floppy for NEC 9800 1.2 MB (3.5', 1K bytes/sector, 360 RPM) is supported: "), chars.Int13_NEC9800Supported},
			{_T("Int 13h - Japanese floppy for Toshiba 1.2 MB (3.5', 360 RPM) is supported: "), chars.Int13_ToshibaSupported},
			{_T("Int 13h - 5.25' / 360 KB floppy services are supported: "), chars.Int13_Floppy360kbSupported},
			{_T("Int 13h - 5.25' / 1.2 MB floppy services are supported: "), chars.Int13_Floppy1p2mbSupported},
			{_T("Int 13h - 3.5' / 720 KB floppy services are supported: "), chars.Int13_Floppy720kbSupported},
			{_T("Int 13h - 3.5'' / 2.88 MB floppy services are supported: "), chars.Int13_Floppy2p8mbSupported},
			{_T("Int 5h (print screen) is supported: "), chars.Int5Supported},
			{_T("Int 9h (i8042) is supported: "), chars.Int9Supported},
			{_T("Int 14h (serial services) is supported: "), chars.Int14Supported},
			{_T("Int 17h (printer services) is supported: "), chars.Int17Supported},
			{_T("Int 10h (CGA/Mono Video services) is supported: "), chars.Int10Supported},
			{_T("NEC PC-98: "), chars.NEC_PC98},
			{NULL, NULL}
		};
		#undef chars
		for (UINT i = 0; flags[i].desc != NULL; ++i) {
			std::wcout << _T("\t") << flags[i].desc << std::boolalpha << (bool)(flags[i].val) << _T("\n");
		}
	}
	std::wcout << _T("\n");

	if (g_SMBIOSVersion < MKSMBIOSVERSION(2,1))
		return;

	std::wcout << _T("BIOS Characteristics (extended): ") << _T("\n");
	{
#define chars table->BIOSCharacteristicsEx.Byte1
		BIT_DESC flags[] = {
			{_T("ACPI is supported: "), chars.ACPISupported},
			{_T("USB Legacy is supported: "), chars.USBLegacySupported},
			{_T("AGP is supported: "), chars.AGPSupported},
			{_T("I20 boot is supported: "), chars.I20BootSupported},
			{_T("LS-120 SuperDisk boot is supported: "), chars.LS120BootSupported},
			{_T("ATAPI ZIP drive boot is supported: "), chars.ATAPIZIPBootSupported},
			{_T("1394 Boot is supported: "), chars._1394BootSupported},
			{NULL, NULL}
		};
#undef chars
		std::wcout << _T("Byte 1") << _T("\n");
		for (UINT i = 0; flags[i].desc != NULL; ++i) {
			std::wcout << _T("\t") << flags[i].desc << std::boolalpha << (bool)(flags[i].val) << _T("\n");
		}
	}

	if (g_SMBIOSVersion < MKSMBIOSVERSION(2,3))
		return;

	{
#define chars table->BIOSCharacteristicsEx.Byte2
		BIT_DESC flags[] = {
			{_T("BIOS Boot Specification is supported: "), chars.BIOSBootSpecSupported},
			{_T("Function key-initiated network service boot is supported: "), chars.FKINSBootSupported},
			{_T("Targeted content distribution is enabled: "), chars.TCDEnabled},
			{_T("UEFI Specification is supported: "), chars.UEFISupported},
			{_T("SMBIOS table describes a virtual machine: "), chars.IsVirtualMachine},
			{_T("Manufacturing mode is supported: "), chars.ManufacturingModeSupported},
			{_T("Manufacturing mode is enabled: "), chars.ManufacturingModeEnabled},
			{NULL, NULL}
		};
#undef chars
		std::wcout << _T("Byte 2") << _T("\n");
		for (UINT i = 0; flags[i].desc != NULL; ++i) {
			std::wcout << _T("\t") << flags[i].desc << std::boolalpha << (bool)(flags[i].val) << _T("\n");
		}
	}

	if (g_SMBIOSVersion < MKSMBIOSVERSION(2,4))
		return;

	std::wcout << _T("SMBIOS Version (affected by BIOS upgrades): ");
	if (table->SystemBIOSMajorRelease != 0xFF) {
		std::wcout << table->SystemBIOSMajorRelease << _T(".") << table->SystemBIOSMinorRelease;
	} else {
		std::wcout << _T("Not supported");
	}
	std::wcout << _T("\n");

	std::wcout << _T("Embedded Controller Firmware Version: ");
	if (table->EmbeddedConMajorRelease != 0xFF) {
		std::wcout << table->EmbeddedConMajorRelease << _T(".") << table->EmbeddedConMinorRelease;
	} else {
		std::wcout << _T("Not supported");
	}
	std::wcout << _T("\n");

	std::wcout << _T("(End of Type 0 struct)") << _T("\n");
	return;
}