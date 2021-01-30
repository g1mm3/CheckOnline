#include "samp.h"
#include "Utils.h"

Samp *pSamp;

Samp::Samp()
{
	g_dwSAMP_Addr = NULL;
	stSAMP *g_SAMP = nullptr;
}

bool Samp::Init()
{
	if (g_dwSAMP_Addr == NULL) g_dwSAMP_Addr = (DWORD)GetModuleHandleA("samp.dll");
	if (g_dwSAMP_Addr == NULL) return false;

	if (g_SAMP == nullptr) g_SAMP = *(stSAMP**)(g_dwSAMP_Addr + 0x21A0F8);
	if (g_SAMP == nullptr) return false;

	if (g_SAMP->iGameState != 14) return false;

	return true;
}

stPlayerPool* Samp::GetPlayers()
{
	return g_SAMP->pPools->pPlayer;
}

char* Samp::GetServerHostname()
{
	return g_SAMP->szHostname;
}

void Samp::AddToChatWindow(char *text, DWORD textColor)
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

void Samp::AddClientCommand(const char *command, void *function)
{
	((void(__thiscall *)(DWORD str, const char* cmd, void* func))(g_dwSAMP_Addr + 0x65AD0))(*(DWORD*)(g_dwSAMP_Addr + 0x21A0E8), command, function);
}

D3DCOLOR Samp::GetSampColor(int id, DWORD trans)
{
	if (g_dwSAMP_Addr == NULL)
		return NULL;

	if (!(this->GetPlayers()->iIsListed[id]) && id != this->GetPlayers()->sLocalPlayerID)
	{
		if (id < 0 || id > 1000)
			this->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}Введите id от 0 до 1000!"), -1);
		else
		{
			char bufferString[150];
			snprintf(bufferString, sizeof(bufferString), "{D2691E}[CheckOnline] {FFFFFF}Игрока с id[%d] нет на сервере", id);
			this->AddToChatWindow(PrepareTextToOutput(bufferString), -1);
		}
		
		return 0;
	}

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