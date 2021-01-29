#pragma once
#include <Windows.h>
#include <process.h>
#include <fstream>
#include <io.h> // для _access (344 строка main.cpp)

#include "JSON/json.hpp"
#include "Server.h"
#include "Samp.h"
#include "Utils.h"

using json = nlohmann::json;

json mainJson;