/*
 * main.cpp
 * App entry point
 */

#include "stdafx.h"
#include "app.h"
#include "cmd.h"

INT _tmain(INT argc, TCHAR **argv)
{
	g_argc = argc;
	g_argv = argv;
	app_atstart();

	
	return cmd_main();
}