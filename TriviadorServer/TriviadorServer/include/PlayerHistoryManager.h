#pragma once
#include<PlayerHistory.h>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

static auto CreateStorageForPlayersHistory(const std::string& databaseFileName)
{
	return sql::make_storage(
		databaseFileName,
		sql::make_table(
			"Match",
			sql::make_column("Name", &PlayerHistory::SetUsername, &PlayerHistory::GetUsername),
			sql::make_column("Score", &PlayerHistory::SetScore, &PlayerHistory::GetScore),
			sql::make_column("Rank", &PlayerHistory::SetRank, &PlayerHistory::GetRank)
			)
	); 
}

using StorageForGM = decltype(CreateStorageForPlayersHistory(""));


class PlayerHistoryManager
{
public:
	PlayerHistoryManager() = default;
	PlayerHistoryManager(const std::string& databaseFileName);

	void AddPlayerHistory(PlayerHistory& playerHistory);
	std::vector<PlayerHistory> GetPlayerMatches(const std::string& username);
private:
	StorageForGM m_database;
};
