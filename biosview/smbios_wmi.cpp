#include "stdafx.h"
#include "smbios_wmi.h"
#include "app.h"

/* WMI Services instance */
IWbemServices *pSvc = NULL;
/* WMI Locator instance */
IWbemLocator *pLoc = NULL;

static LPCTSTR taskProps[] = {
	_T("Manufacturer"),
	_T("Name"),
	_T("Version"),
	NULL
};

HRESULT CoInit(VOID)
{
	HRESULT hr = S_OK;

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		app_error(_T("Failed to initialize COM"));
		goto fail;
	}

	hr = CoInitializeSecurity(
		NULL,                        // Security descriptor
		-1,                          // COM negotiates authentication service
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication level for proxies
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation level for proxies
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities of the client/server
		NULL                         // Reserved
	);
	if (FAILED(hr)) {
		app_error(_T("Failed to initialize COM security"));
		goto fail;
	}

fail:
	return hr;
}

HRESULT WMIConnect(VOID)
{
	HRESULT hr = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator,
		(LPVOID *)&pLoc
	);
	if (FAILED(hr)) {
		app_error(_T("Failed to connect to WMI server"));
		goto fail;
	}

	hr = pLoc->ConnectServer(
		(BSTR)_T("ROOT\\CimV2"),
		NULL, NULL, NULL,
		0, 0,
		NULL, &pSvc
	);
	if (FAILED(hr)) {
		app_error(_T("Failed to connect to WMI server"));
		goto fail;
	}

	// Set the proxy so that impersonation of the client occurs.
	hr = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx 
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx 
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities
	);

	if (FAILED(hr)) {
		app_error(_T("Failed to connect to WMI server proxy"));
		goto fail;
	}

fail:
	return hr;
}

VOID WMIClose(VOID)
{
	pSvc->Release();
	pLoc->Release();
	return;
}


HRESULT GetSMBIOSFromWMI(VOID)
{
	HRESULT hr = S_OK;
	IWbemClassObject *pObj = NULL;
	IEnumWbemClassObject *pEnum = NULL;
	CIMTYPE cimtype = 0;
	VARIANT v;
	VariantInit(&v);

	hr = pSvc->ExecQuery(
		(BSTR)_T("WQL"),
		(BSTR)_T(
			"SELECT * "
			"FROM Win32_BIOS"
		),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL, &pEnum
	);
	if (FAILED(hr)) {
		app_error(_T("Query from Win32_BIOS failed"));
		goto fail;
	}

	while (1) {
		ULONG uRet = 0;
		hr = pEnum->Next(WBEM_INFINITE, 1, &pObj, &uRet);
		if (uRet == 0)
			break;
		for (LPCTSTR *prop = taskProps; *prop; prop++) {
			HRESULT get_res = pObj->Get(
				*prop, 0,
				&v, &cimtype, 0
			);
			if (FAILED(get_res))
				break;
			std::wcout << *prop << _T(": ");
			switch (cimtype) {
			case CIM_STRING:
				std::wcout << V_BSTR(&v);
				break;
			case CIM_SINT16:
			case CIM_SINT32:
			case CIM_SINT64:
				std::wcout << V_I8(&v);
				break;
			case CIM_UINT16:
			case CIM_UINT32:
			case CIM_UINT64:
			default:
				std::wcout << V_UI8(&v);
				break;
			}
			std::wcout << _T("\n");
		}

	}

fail:
	pEnum->Release();
	pObj->Release();
	VariantClear(&v);
	return hr;
}