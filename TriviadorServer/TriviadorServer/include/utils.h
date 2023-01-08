#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "Player.h"
#include "Board.h"

std::vector<std::string> Split(const std::string& str, const std::string& delim);
std::unordered_map<std::string, std::string> ParseUrlArgs(const std::string& urlArgs);

void to_json(nlohmann::json& json, const Player& player);
void to_json(nlohmann::json& json, const Territory& territory);