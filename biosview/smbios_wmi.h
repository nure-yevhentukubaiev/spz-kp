#pragma once
#include "stdafx.h"

HRESULT CoInit(VOID);

VOID WMIClose(VOID);

HRESULT WMIConnect(VOID);

HRESULT GetSMBIOSFromWMI(VOID);