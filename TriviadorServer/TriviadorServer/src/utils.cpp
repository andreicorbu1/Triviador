#include "utils.h"
std::vector<std::string> Split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> result;
	size_t startIndex = 0;

	for (size_t found = str.find(delim); found != std::string::npos; found = str.find(delim, startIndex))
	{
		result.emplace_back(str.begin() + startIndex, str.begin() + found);
		startIndex = found + delim.size();
	}
	if (startIndex != str.size())
		result.emplace_back(str.begin() + startIndex, str.end());
	return result;
}

std::unordered_map<std::string, std::string> ParseUrlArgs(const std::string& urlArgs)
{
	if (urlArgs == "")
	{
		return {};
	}

	std::unordered_map<std::string, std::string> result;
	for (const auto& kvStr : Split(urlArgs, "&"))
	{
		auto kvVector = Split(kvStr, "=");
		if (kvVector.size() == 2)
			result[kvVector[0]] = kvVector[1];
	}
	return result;
}

// to_json Overloads
void to_json(nlohmann::json& json, const Player& player)
{
	json =
	{
		{"name", player.GetName()},
		{"color", Player::ToString(player.GetColor())},
		{"score", player.GetScore()}
	};
}

void to_json(nlohmann::json& json, const PlayerHistory& playerHistory)
{
	json =
	{
		{"id", playerHistory.GetID()},
		{"score", playerHistory.GetScore()},
		{"rank", playerHistory.GetRank()}
	};
}

void to_json(nlohmann::json& json, const Territory& territory)
{
	Player owner = territory.GetOwner().has_value() ? territory.GetOwner().value() : Player();
	uint16_t score = territory.GetScore();
	bool isBase = territory.GetIsBase();
	json =
	{
		{"owner", owner},
		{"score", score},
		{"base", isBase}
	};
}
