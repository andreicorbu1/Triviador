#pragma once
#include<Player.h>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

static auto CreateStorageForPlayers(const std::string& databaseFileName)
{
	return sql::make_storage(
		databaseFileName,
		sql::make_table(
			"Player",
			sql::make_column("Name", &Player::SetName, &Player::GetName),
			sql::make_column("Score", &Player::SetScore, &Player::GetScore),
			sql::make_column("Rank", &Player::SetRank, &Player::GetRank)
			)
	); 
}

using StorageForGM = decltype(CreateStorageForPlayers(""));


class PlayerHistoryManager
{
public:
	PlayerHistoryManager() = default;
	PlayerHistoryManager(const std::string& databaseFileName);

	void AddPlayer(Player& Player);
	std::vector<Player> GetPlayerMatches(const std::string& username);
private:
	StorageForGM m_database;
};
