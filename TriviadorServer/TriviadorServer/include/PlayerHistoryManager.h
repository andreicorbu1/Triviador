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
			sql::make_column("id", &PlayerHistory::SetID, &PlayerHistory::GetID),
			sql::make_column("userame", &PlayerHistory::SetUsername, &PlayerHistory::GetUsername),
			sql::make_column("score", &PlayerHistory::SetScore, &PlayerHistory::GetScore),
			sql::make_column("rank", &PlayerHistory::SetRank, &PlayerHistory::GetRank)
			)
	); 
}

using StorageForGM = decltype(CreateStorageForPlayersHistory(""));


class PlayerHistoryManager
{
public:
	PlayerHistoryManager() = default;
	PlayerHistoryManager(const std::string& databaseFileName);

	void AddPlayerHistory(const PlayerHistory& playerHistory);
	std::vector<PlayerHistory> GetPlayerMatches(const std::string& username);
private:
	StorageForGM m_database;
};
