#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "JSON/json.hpp"
#include "Utils.h"

class Server
{
public:
	std::string name;

	std::vector<std::vector<std::vector<std::string>>> groupClists;

	Server::Server(char hostname[259], const nlohmann::json& j);

	void InitClists();
	void Server::InitClists(const nlohmann::json& j);
};

extern Server* pServer;