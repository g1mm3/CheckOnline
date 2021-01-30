#include "Server.h"
#include <iomanip> // std::setw

Server* pServer;

// groupTypesCount = groupClists.size();

Server::Server(char hostname[259], const nlohmann::json& j)
{
	for (auto& el : j.items())
	{
		if (strstr(hostname, el.key().c_str()))
		{
			this->name = el.key();
			break;
		}
	}

	if (j.find(this->name) == j.end())
	{
		this->name = "";
		return;
	}

	std::vector<std::vector<std::vector<std::string>>> tempArray = j[this->name];
	this->groupClists = tempArray;
}

void Server::InitClists()
{
	std::ifstream ifs("CheckOnline.json");
	nlohmann::json j = nlohmann::json::parse(ifs);

	std::vector<std::vector<std::vector<std::string>>> tempArray = j[this->name];
	this->groupClists = tempArray;
}

// Это для записи/перезаписи
void Server::InitClists(const nlohmann::json& j)
{
	std::ofstream file("CheckOnline.json");
	file << std::setw(2) << j << std::endl;

	std::vector<std::vector<std::vector<std::string>>> tempArray = j[this->name];
	this->groupClists = tempArray;
}