#include "main.h"

stSAMP *g_SAMP = nullptr;
stPlayerPool *g_Players = nullptr;
extern uint32_t g_dwSAMP_Addr; // описание переменной

void addToChatWindow(char *text, DWORD textColor)
{
	if (!g_dwSAMP_Addr)
		return;
	if (!text)
		return;

	DWORD	chatinfo = g_dwSAMP_Addr + 0x21A0E4;
	DWORD	func = g_dwSAMP_Addr + 0x64010;

	__asm mov eax, dword ptr[chatinfo]
		__asm mov ecx, dword ptr[eax]
		__asm push 0
	__asm push textColor
	__asm push 0
	__asm push text
	__asm push 8
	__asm call func
}

void addClientCommand(const char *command, void *function)
{
	((void(__thiscall *)(DWORD str, const char* cmd, void* func))(g_dwSAMP_Addr + 0x65AD0))(*(DWORD*)(g_dwSAMP_Addr + 0x21A0E8), command, function);
}

D3DCOLOR samp_color_get(int id, DWORD trans)
{
	if (g_dwSAMP_Addr == NULL)
		return NULL;

	D3DCOLOR	*color_table;
	if (id < 0 || id >= (1004 + 3))
		return D3DCOLOR_ARGB(0xFF, 0x99, 0x99, 0x99);

	switch (id)
	{
	case (1004):
		return 0xFF888888;

	case (1004 + 1):
		return 0xFF0000AA;

	case (1004 + 2):
		return 0xFF63C0E2;
	}

	color_table = (D3DCOLOR *)((uint8_t *)g_dwSAMP_Addr + 0x216378);
	return (color_table[id] >> 8) | trans;
}