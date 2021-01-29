#include "Utils.h"

std::string DecimalToHeximal(int dec)
{
	char hex[20];
	_itoa(dec, hex, 16);
	return hex;
}

int HeximalToDecimal(std::string hex)
{
	return std::stoul(hex, nullptr, 16);
}

std::string StringToUpperCase(std::string str)
{
	for (auto& c : str) c = toupper(c);
	return str;
}

char* PrepareTextToOutput(char* text)
{
	return StringToCharPointer(UTF8_to_CP1251(text));
}

char* PrepareTextToOutput(std::string text)
{
	return const_cast<char*>(text.c_str());
}

std::string UTF8_to_CP1251(std::string const& utf8)
{
	if (!utf8.empty())
	{
		int wchlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), NULL, 0);
		if (wchlen > 0 && wchlen != 0xFFFD)
		{
			std::vector<wchar_t> wbuf(wchlen);
			MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), &wbuf[0], wchlen);
			std::vector<char> buf(wchlen);
			WideCharToMultiByte(1251, 0, &wbuf[0], wchlen, &buf[0], wchlen, 0, 0);

			return std::string(&buf[0], wchlen);
		}
	}
	return std::string();
}

std::string CP1251_to_UTF8(const char* str)
{
	std::string res;
	int result_u, result_c;
	result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (!result_u) { return 0; }
	wchar_t* ures = new wchar_t[result_u];
	if (!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)) {
		delete[] ures;
		return 0;
	}
	result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
	if (!result_c) {
		delete[] ures;
		return 0;
	}
	char* cres = new char[result_c];
	if (!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)) {
		delete[] cres;
		return 0;
	}
	delete[] ures;
	res.append(cres);
	delete[] cres;
	return res;
}

char* StringToCharPointer(std::string str)
{
	return const_cast<char*>(str.c_str());
}