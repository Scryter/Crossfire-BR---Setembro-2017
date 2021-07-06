#include "opt.h"

__declspec(naked) HRESULT WINAPI PresentMidfunction()
{
	static LPDIRECT3DDEVICE9 pDevice;

	__asm
	{
		MOV ECX, DWORD PTR DS : [EAX]
		MOV EDX, DWORD PTR DS : [ECX + 0x44]
			MOV DWORD PTR DS : [pDevice], EAX
			PUSH 0
			PUSHAD
	}



	CriarFonte(pDevice);
	RENDMENU(pDevice);


	__asm
	{
		POPAD
		JMP retPresentEngine
	}
}

VOID *DetourCreate(BYTE *src, CONST BYTE *dst, CONST INT len)
{
	BYTE *jmp = (BYTE *)malloc(len + 5);
	DWORD dwBack;

	VirtualProtect(src, len, PAGE_READWRITE, &dwBack);
	memcpy(jmp, src, len);
	jmp += len;
	jmp[0] = 0xE9;
	*(DWORD *)(jmp + 1) = (DWORD)(src + len - jmp) - 5;

	src[0] = 0xE9;
	*(DWORD *)(src + 1) = (DWORD)(dst - src) - 5;
	for (INT i = 5; i < len; i++)
		src[i] = 0x90;
	VirtualProtect(src, len, dwBack, &dwBack);

	return(jmp - len);
}

DWORD WINAPI StartRoutine(LPVOID)
{
	while (TRUE)
	{
		if (memcmp((VOID *)PresentEngine, (VOID *)(PBYTE)"\x8B\x51", 2) == 0)
		{
			Sleep(100);
			DetourCreate((PBYTE)PresentEngine, (PBYTE)PresentMidfunction, 5);
		}
		Sleep(50);
	}

	return 0;
}
