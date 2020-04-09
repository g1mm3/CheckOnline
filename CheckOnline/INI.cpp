#include "INI.h"

void INI::WriteString(LPCSTR AppName, LPCSTR KeyName, LPCSTR String, LPCSTR FileName)
{
	WritePrivateProfileStringA(AppName, KeyName, String, FileName);
}

std::string INI::ReadString(LPCSTR AppName, LPCSTR KeyName, DWORD Size, LPCSTR FileName)
{
	char* tempString = new char[Size];
	GetPrivateProfileStringA(AppName, KeyName, NULL, tempString, Size, FileName);
	std::string ReturnedString = tempString;
	delete tempString;
	return ReturnedString;
}

void INI::WriteInt(LPCSTR AppName, LPCSTR KeyName, INT Number, LPCSTR FileName)
{
	WritePrivateProfileStringA(AppName, KeyName, std::to_string(Number).c_str(), FileName);
}

INT INI::GetInt(LPCSTR AppName, LPCSTR KeyName, DWORD Size, LPCSTR FileName)
{
	char* tempString = new char[Size];
	GetPrivateProfileStringA(AppName, KeyName, NULL, tempString, Size, FileName);
	std::string ReturnedString = tempString;
	delete tempString;
	return atoi(ReturnedString.c_str());
}

void INI::WriteFloat(LPCSTR AppName, LPCSTR KeyName, FLOAT Number, LPCSTR FileName)
{
	WritePrivateProfileStringA(AppName, KeyName, std::to_string(Number).c_str(), FileName);
}

FLOAT INI::GetFloat(LPCSTR AppName, LPCSTR KeyName, DWORD Size, LPCSTR FileName)
{
	char* tempString = new char[Size];
	GetPrivateProfileStringA(AppName, KeyName, NULL, tempString, Size, FileName);
	std::string ReturnedString = tempString;
	delete tempString;
	return atof(ReturnedString.c_str());
}