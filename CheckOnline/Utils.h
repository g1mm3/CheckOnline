#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include "JSON/json.hpp"


std::string DecimalToHeximal(int dec);
int HeximalToDecimal(std::string hex);

std::string StringToUpperCase(std::string str);
char* PrepareTextToOutput(char* text);
char* PrepareTextToOutput(std::string text);
std::string UTF8_to_CP1251(std::string const& utf8);
std::string CP1251_to_UTF8(const char* str);
char* StringToCharPointer(std::string str);