#pragma once
#include <iostream>
#include <string>
#include <process.h>
#include <fstream>
#include <windows.h>

#include <D3D9Types.h>
#include "INI.h"
#include "samp.h"


// 
inline bool IsFileExist(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}