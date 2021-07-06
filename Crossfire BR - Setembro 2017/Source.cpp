#include "hook.h"

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hDll);
		MessageBox(0, "Hook Present Engine", "Crossfire", 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartRoutine, NULL, NULL, NULL);
	}

	return TRUE;
}