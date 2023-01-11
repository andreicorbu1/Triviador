#include "PlayerHistoryManager.h"

PlayerHistoryManager::PlayerHistoryManager(const std::string& databaseFileName)
	:m_database(CreateStorageForPlayersHistory(databaseFileName))
{
	m_database.sync_schema();
}

void PlayerHistoryManager::AddPlayerHistory(const PlayerHistory& playerHistory)
{
	m_database.insert(playerHistory);
}

std::vector<PlayerHistory> PlayerHistoryManager::GetPlayerMatches(const std::string& username)
{
	std::vector<PlayerHistory> all_games = m_database.get_all<PlayerHistory>(sql::where(sql::in(&PlayerHistory::GetUsername, {username})));
	if (all_games.size() > 10)
	{
		std::vector<PlayerHistory> last10Games;
		last10Games.insert(last10Games.begin(), all_games.end() - 10, all_games.end());
		return last10Games;
	}
	return all_games;
}