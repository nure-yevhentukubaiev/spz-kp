/*
 * stdafx.h
 * Precompiled header
 */
#pragma once

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// 
#define _WIN32_DCOM
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include <wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")