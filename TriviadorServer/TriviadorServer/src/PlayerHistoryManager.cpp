#include "PlayerHistoryManager.h"

PlayerHistoryManager::PlayerHistoryManager(const std::string& databaseFileName)
	:m_database(CreateStorageForPlayersHistory(databaseFileName))
{
	m_database.sync_schema();
}

void PlayerHistoryManager::AddPlayerHistory(PlayerHistory& playerHistory)
{
	m_database.insert(playerHistory);
}

std::vector<PlayerHistory> PlayerHistoryManager::GetPlayerMatches(const std::string& username)
{
	return m_database.get_all<PlayerHistory>(sql::where(sql::in(&PlayerHistory::GetUsername, {username})));
}