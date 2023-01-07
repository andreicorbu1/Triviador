#include "GameManager.h"

GameManager::GameManager(const std::string& databaseFileName)
	:m_database(CreateStorageForGames(databaseFileName))
{
	m_database.sync_schema();
}

void GameManager::AddGame(Game& game)
{
	auto numberOfPlayers = game.GetNumberOfPlayers();
	if (numberOfPlayers != 4)
	{
		for (size_t i = 0; i < 4 - numberOfPlayers; i++)
		{
			game.AddNullPlayer();
		}
	}
		m_database.insert(game);
}
