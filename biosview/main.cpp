/*
 * main.cpp
 * App entry point
 */

#include "stdafx.h"

INT _tmain(INT argc, TCHAR **argv)
{	
	for (UINT i = 0; i < argc; ++i)
		_tprintf(_T("%s\n"), argv[i]);
	return 0;
}