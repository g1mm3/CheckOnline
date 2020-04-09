#include <Windows.h>
#include <String>
#pragma comment(lib, "user32.lib")

namespace INI
{
	void WriteString(LPCSTR AppName, LPCSTR KeyName, LPCSTR String, LPCSTR FileName);
	std::string ReadString(LPCSTR AppName, LPCSTR KeyName, DWORD Size, LPCSTR FileName);
	void WriteInt(LPCSTR AppName, LPCSTR KeyName, INT Number, LPCSTR FileName);
	INT GetInt(LPCSTR AppName, LPCSTR KeyName, DWORD Size, LPCSTR FileName);
	void WriteFloat(LPCSTR AppName, LPCSTR KeyName, FLOAT Number, LPCSTR FileName);
	FLOAT GetFloat(LPCSTR AppName, LPCSTR KeyName, DWORD Size, LPCSTR FileName);
}