// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "includes.h"
#include "mem2.h"

HWND hwnd;

BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam)
{
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid);
	if (dwPid == lParam)
	{
		hwnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

HWND get_process_window()
{
	if (hwnd)
		return hwnd;

	EnumWindows(EnumWindowCallBack, GetCurrentProcessId());

	if (hwnd == NULL)
		0;
	return hwnd;
}



BOOL APIENTRY DllMain(HMODULE hmodule, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		StartPoint::Init();
		//utility::I_beginthreadex(0, 0, (_beginthreadex_proc_type) , 0, 0, 0);




	}
	return TRUE;
}



