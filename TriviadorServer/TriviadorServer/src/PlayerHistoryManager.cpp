#include "PlayerHistoryManager.h"

PlayerHistoryManager::PlayerHistoryManager(const std::string& databaseFileName)
	:m_database(CreateStorageForPlayers(databaseFileName))
{
	m_database.sync_schema();
}

void PlayerHistoryManager::AddPlayer(Player& Player)
{
	m_database.insert(Player);
}

std::vector<Player> PlayerHistoryManager::GetPlayerMatches(const std::string& username)
{
	return m_database.get_all<Player>(sql::where(sql::in(&Player::GetName, {username})));
}

//std::vector<Game> GameManager::GetAll(const std::string& username)
//{
//	std::vector<Game> auxVector1, auxVector2, auxVector3, auxVector4;
//	auxVector1 = m_database.get_all<Game>(sql::where(sql::in(&Game::GetPlayerName<0>, { username })));
//	auxVector2 = m_database.get_all<Game>(sql::where(sql::in(&Game::GetPlayerName<1>, { username })));
//	auxVector3 = m_database.get_all<Game>(sql::where(sql::in(&Game::GetPlayerName<2>, { username })));
//	auxVector4 = m_database.get_all<Game>(sql::where(sql::in(&Game::GetPlayerName<3>, { username })));
//	auxVector1.insert(auxVector1.end(), auxVector2.begin(), auxVector2.end());
//	auxVector1.insert(auxVector1.end(), auxVector3.begin(), auxVector3.end());
//	auxVector1.insert(auxVector1.end(), auxVector4.begin(), auxVector4.end());
//	std::vector<Game> auxVector = m_database.get_all<Game>();
//	/*for (const auto& var : m_database.iterate<Game>())
//	{
//		std::cout << var.GetGameID();
//	}*/
//
//	return auxVector;
//}
