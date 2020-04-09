#include "main.h"

uint32_t g_dwSAMP_Addr = NULL; // ���������� ����������
int serverId;
const int serversCount = 6;
const int typesCount = 3;
const int maxGroupsCount = 5;

std::string clists[serversCount][typesCount][maxGroupsCount];

std::string names[serversCount][typesCount][maxGroupsCount] =
{
	// Advance RP
	{
		{
			"Grove",
			"Ballas",
			"Vagos",
			"Rifa",
			"Aztec"
		},
		{
			"LCN",
			"Yakuza",
			"Russian"
		},
		{
			"Masked",
			"Bomj"
		}
	},

	// Samp RP
	{
		{
			"Grove",
			"Ballas",
			"Vagos",
			"Rifa",
			"Aztec"
		},
		{
			"LCN",
			"Yakuza",
			"Russian"
		},
		{
			"Masked",
			"Bomj"
		}
	},

	// Arizona RP
	{
		{
			"Grove",
			"Ballas",
			"Vagos",
			"Rifa",
			"Aztec"
		},
		{
			"LCN",
			"Yakuza",
			"Russian",
			"Warlock"
		},
		{
			"Wolfs",
			"Masked",
			"Bomj"
		}
	},

	// Diamond RP
	{
		{
			"Grove",
			"Ballas",
			"Vagos",
			"Rifa",
			"Aztec"
		},
		{
			"Mexican",
			"Yakuza",
			"Columbian"
		},
		{
			"Masked",
			"Bomj"
		}
	},

	// Evolve RP
	{
		{
			"Grove",
			"Ballas",
			"Vagos",
			"Rifa",
			"Aztec"
		},
		{
			"LCN",
			"Yakuza",
			"Russian"
		},
		{
			"Masked",
			"Bomj"
		}
	},

	// Pears Project
	{
		{
			"Grove",
			"Ballas",
			"Vagos",
			"Aztec"
		},
		{
			"LCN",
			"Yakuza",
			"Russian",
			"Arabian"
		},
		{
			"Triada",
			"Hitmans",
			"Bomj"
		}
	}
};

int GetCurrentServer(char hostname[259])
{
	if (strstr(hostname, "Advance"))
		return 0;
	else if (strstr(hostname, "Samp-Rp"))
		return 1;
	else if (strstr(hostname, "Arizona Role Play"))
		return 2;
	else if (strstr(hostname, "Diamond Role Play"))
		return 3;
	else if (strstr(hostname, "Evolve-Rp"))
		return 4;
	else if (strstr(hostname, "Pears"))
		return 5;
	else
		return 6;
}

std::string GetServerNameById(int servId)
{
	switch (servId)
	{
		case 0 : 
			return "Advance RP";
			break;
		case 1 :
			return "Samp-Rp";
			break;
		case 2 :
			return "Arizona RP";
			break;
		case 3 :
			return "Diamond RP";
			break;
		case 4 :
			return "Evolve-Rp";
			break;
		case 5 :
			 return "Pears Project";
			 break;
		default :
			return "";
			break;
	}
}

uint32_t HeximalToDecimal(std::string h)
{
	// plan:
	// without 0x

	const int length = h.length();
	uint32_t dec = 0;

	int to;

	for (int i = 0; i < length; i++)
	{
		switch (h[i])
		{
		case '1': to = 1; break;
		case '2': to = 2; break;
		case '3': to = 3; break;
		case '4': to = 4; break;
		case '5': to = 5; break;
		case '6': to = 6; break;
		case '7': to = 7; break;
		case '8': to = 8; break;
		case '9': to = 9; break;
		case 'A': to = 10; break;
		case 'B': to = 11; break;
		case 'C': to = 12; break;
		case 'D': to = 13; break;
		case 'E': to = 14; break;
		case 'F': to = 15; break;

		default: continue;
		}

		dec = dec + to * int(pow(16, length - (i + 1)));
	}

	return dec;
}

std::string DecimalToHeximal(uint32_t dec)
{
	std::string digits[16] = { "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F" };
	std::string hex;
	do
	{
		hex.insert(0, digits[dec % 16]);
		dec /= 16;
	} while (dec != 0);
	return hex;
}

bool SampInit()
{
	if (g_dwSAMP_Addr == NULL)    g_dwSAMP_Addr = (DWORD)GetModuleHandle("samp.dll");
	if (g_dwSAMP_Addr == NULL)    return false;

	if (g_SAMP == nullptr)        g_SAMP = *(stSAMP**)(g_dwSAMP_Addr + 0x21A0F8);
	if (g_SAMP == nullptr)        return false;

	return true;
}

void InitClists()
{
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 5; i++)
		{
			clists[serverId][k][i] = INI::ReadString(GetServerNameById(serverId).c_str(), names[serverId][k][i].c_str(), 9, ".\\CheckOnline.ini");
		}
	}
}

inline bool IsFileExist(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void cho()
{

	if (!g_SAMP->pPools->pPlayer)
		return;

	if (serverId == 6)
	{
		addToChatWindow("{D2691E}[CheckOnline] {FFFFFF}������ ������ �� ��������������!", -1);
		return;
	}

	std::string s;
	std::string color;
	std::string name;
	std::string text;
	std::string buf;

	int online = 0;
	char* chr;

	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (clists[serverId][k][i] == "")
				continue;

			for (int j = 0; j < 1004; j++)
			{
				if (g_SAMP->pPools->pPlayer->iIsListed[j])
				{
					if (samp_color_get(j) == HeximalToDecimal(clists[serverId][k][i]))
					{
						online++;
					}
				}
			}
			s = clists[serverId][k][i];
			color = s.erase(0, 2);
			name = names[serverId][k][i];
			buf = name + ": {" + color + "}" + std::to_string(online) + "{FFFFFF} | ";
			text += buf;
			online = 0;
		}
		chr = const_cast<char*>(text.c_str());
		addToChatWindow(chr, -1);

		text = "";
	}
}

void cho_rep(char *param)
{
	if (g_SAMP == NULL)
		return;

	int id;
	char org[50];

	if (!strlen(param) || sscanf(param, "%d %s", &id, &org) < 2)
		return addToChatWindow("{D2691E}[CheckOnline] {FFFFFF}������� ������� � �������: /cho_rep [ID] [�����������]. ������: /cho_rep 4 ������", -1);

	uint32_t color;
	char finalMessage[150];

	if (g_SAMP->pPools->pPlayer->iIsListed[id])
		color = samp_color_get(id);
	else
	{
		if (id < 0 || id > 1000)
			addToChatWindow("{D2691E}[CheckOnline] {FFFFFF}������� ID �� 0 �� 1000!", -1);
		else
		{
			snprintf(finalMessage, sizeof(finalMessage), "{D2691E}[CheckOnline] {FFFFFF}������ � ID[%d] ��� �� �������", id);
			addToChatWindow(finalMessage, -1);
		}
		return;
	}

	INI::WriteString(GetServerNameById(serverId).c_str(), org, DecimalToHeximal(color).c_str(), ".\\CheckOnline.ini");
	InitClists();

	std::string hexEditedColor = DecimalToHeximal(color).erase(0, 2);
	std::string finalMessageString = "{D2691E}[CheckOnline] {FFFFFF}�������! �����������: %s | ����: {" + hexEditedColor + "}%s";

	snprintf(finalMessage, sizeof(finalMessage), finalMessageString.c_str(), org, hexEditedColor.c_str());
	addToChatWindow(finalMessage, -1);
}

int main()
{

	while (!SampInit())
		Sleep(500);

	while (g_SAMP->iGameState != 14)
		Sleep(100);

	if (IsFileExist(".\\CheckOnline.ini"))
		InitClists();
	else
	{
		addToChatWindow("{D2691E}[CheckOnline] {FFFFFF}� ��� ����������� ���� CheckOnline.ini", -1);
		return 0;
	}

	serverId = GetCurrentServer(g_SAMP->szHostname);
	addClientCommand("cho", cho);
	addClientCommand("cho_rep", cho_rep);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		_beginthread(_beginthread_proc_type(main), NULL, NULL);
	}
	return TRUE;
}