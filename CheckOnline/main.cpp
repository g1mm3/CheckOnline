#include "main.h"
// #include <iostream> // 

HMODULE hModule = NULL;

// Команды чата
void cho()
{
	if (!pSamp->GetPlayers())
		return;

	pServer->InitClists();

	std::string color, name, buf;
	std::string text = "";

	int online = 0;

	for (int i = 0; i < pServer->groupClists.size(); i++)
	{
		for (int j = 0; j < pServer->groupClists[i].size(); j++)
		{
			if (pServer->groupClists[i][j][1].empty())
				continue;

			for (int k = 0; k < 1004; k++)
			{
				if (pSamp->GetPlayers()->iIsListed[k])
				{
					if (pSamp->GetSampColor(k) == HeximalToDecimal(pServer->groupClists[i][j][1]))
					{
						online++;
					}
				}
			}
			color = pServer->groupClists[i][j][1].erase(0, 2); // getting clist color w/o first two characters
			name = pServer->groupClists[i][j][0];
			buf = name + ": {" + color + "}" + std::to_string(online) + "{FFFFFF} | ";
			text += buf;
			online = 0;
		}
		pSamp->AddToChatWindow(PrepareTextToOutput(text), -1);

		text = "";
	}
}

void cho_cl(char *param)
{
	if (!pSamp->GetPlayers())
		return;

	int id;
	char organization[30];

	if (!strlen(param) || sscanf(param, "%d %s", &id, &organization) < 2)
	{
		pSamp->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}Введите команду в формате: /cho_cl [id] [организация]. Пример: /cho_rep 4 Aztec"), -1);
		return;
	}

	uint32_t color = pSamp->GetSampColor(id);
	if (color == 0)
		return;

	char bufferString[150];
	// провека на то, что указанная организация обозначена для текущего сервера
	for (int i = 0; i < pServer->groupClists.size(); i++)
	{
		for (int j = 0; j < pServer->groupClists[i].size(); j++)
		{
			if (pServer->groupClists[i][j][0] == organization)
			{
				mainJson[pServer->name][i][j][1] = StringToUpperCase(DecimalToHeximal(color));
				
				pServer->InitClists(mainJson);

				snprintf(bufferString, sizeof(bufferString), "{D2691E}[CheckOnline] {FFFFFF}Успешно! Организация: %s | Цвет: {%s}%s",
					organization,
					StringToUpperCase(DecimalToHeximal(color).erase(0, 2)).c_str(),
					StringToUpperCase(DecimalToHeximal(color).erase(0, 2)).c_str()
				);

				pSamp->AddToChatWindow(PrepareTextToOutput(bufferString), -1);
				return;
			}
		}
	}

	pServer->InitClists();
	
	// если указанной организации нет в списках -> вывод тех, которые есть
	std::string clr, name, buf;
	std::string text = "";
	pSamp->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}Введите корректную организацию! Вот список допустимых названий организаций: "), -1);
	for (int i = 0; i < pServer->groupClists.size(); i++)
	{
		for (int j = 0; j < pServer->groupClists[i].size(); j++)
		{
			clr = pServer->groupClists[i][j][1].erase(0, 2); // getting clist color w/o first two characters
			name = pServer->groupClists[i][j][0];
			buf = "{" + clr + "}" + name + " | " ;
			text += buf;
		}
		pSamp->AddToChatWindow(PrepareTextToOutput(text), -1);
		text = "";
	}
}

void cho_add(char* param)
{
	if (!pSamp->GetPlayers())
		return;

	int id;
	char tagName[30];

	if (!strlen(param) || sscanf(param, "%d %s", &id, &tagName) < 2)
	{
		pSamp->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}Введите команду в формате: /cho_add [id] [tag]. Например: /cho_add 220 таксисты"), -1);
		return;
	}

	uint32_t color = pSamp->GetSampColor(id);
	if (color == 0)
		return;

	if (mainJson.find("Z_Polygon") == mainJson.end())
	{
		pSamp->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}В файле CheckOnline.json нет секции Polygon"), -1);
		return;
	}

	int polygonSize = mainJson["Z_Polygon"].size();


	mainJson["Z_Polygon"][polygonSize][0] = CP1251_to_UTF8(tagName);
	mainJson["Z_Polygon"][polygonSize][1] = StringToUpperCase(DecimalToHeximal(color));

	pServer->InitClists(mainJson);

	char bufferString[150];
	snprintf(bufferString, sizeof(bufferString), "{D2691E}[CheckOnline] {FFFFFF}Успешно! Тег: %s | Цвет: {%s}%s",
		CP1251_to_UTF8(tagName).c_str(),
		StringToUpperCase(DecimalToHeximal(color).erase(0, 2)).c_str(),
		StringToUpperCase(DecimalToHeximal(color).erase(0, 2)).c_str()
	);

	pSamp->AddToChatWindow(PrepareTextToOutput(bufferString), -1);
}

void cho_rt()
{
	if (pServer)
		delete pServer;

	// Проверка на существование файла (если не существует -> создать)
	if (_access(".\\CheckOnline.json", 0))
	{
		std::ofstream file(".\\CheckOnline.json");
		file << mainJson;
	}

	// Читка JSON-файла
	std::ifstream ifs("CheckOnline.json");
	mainJson = json::parse(ifs);

	pServer = new Server(pSamp->GetServerHostname(), mainJson);
	pSamp->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}Перезагрузка выполнена успешно!"), -1);
}

// MAIN
int main()
{
	// Проверка: загружена ли игра
	while (*(DWORD*)0xC8D4C0 != 9)
		Sleep(350);

	
	// Инициализация сампа
	if (GetModuleHandleA("samp.dll"))
	{
		pSamp = new Samp();

		while (!pSamp->Init())
			Sleep(350);
	}
	else
	{
		if (pSamp)
			delete pSamp;

		FreeLibraryAndExitThread(hModule, 0);
	}

	// Проверка на существование файла (если не существует -> создать)
	if (_access("CheckOnline.json", 0))
	{
		std::ofstream file("CheckOnline.json");
		file << mainJson;
	}

	// Читка JSON-файла
	std::ifstream ifs("CheckOnline.json");
	// это, чтобы плагин не крашнулся, если при читке произойдет какая-то ошибка
	try
	{
		mainJson = json::parse(ifs);
	}
	catch(std::exception e)
	{
		pSamp->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}При инициализации JSON-файла произошла ошибка!"), -1);
		pSamp->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}Возможно, вы не убрали запятые после последних элементов!"), -1);
		return 0;
	}

	if (mainJson.dump() == "null" || mainJson.dump() == "")
	{
		pSamp->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}Ваш JSON-файл пуст!"), -1);
		return 0;
	}

	pServer = new Server(pSamp->GetServerHostname(), mainJson);

	if (pServer->name == "")
	{
		pSamp->AddToChatWindow(PrepareTextToOutput("{D2691E}[CheckOnline] {FFFFFF}Данный сервер не поддерживается!"), -1);
		delete pServer;
		return 0;
	}

	pServer->InitClists();

	// Регистрация команд
	pSamp->AddClientCommand("cho", cho);
	pSamp->AddClientCommand("cho_cl", cho_cl);
	pSamp->AddClientCommand("cho_add", cho_add);
	pSamp->AddClientCommand("cho_rt", cho_rt);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		// Консоль для дебага
		// AllocConsole();
		//freopen("CONIN$", "r", stdin);
		//freopen("CONOUT$", "w", stdout);

		DisableThreadLibraryCalls(module);
		hModule = module;
		_beginthread(_beginthread_proc_type(main), NULL, NULL);
	}
	return TRUE;
}