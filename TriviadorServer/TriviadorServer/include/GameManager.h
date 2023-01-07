#pragma once
#include<Game.h>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

static auto CreateStorageForGames(const std::string& databaseFileName)
{
	return sql::make_storage(
		databaseFileName,
		sql::make_table(
			"Game",
			sql::make_column("id", &Game::SetGameID, &Game::GetGameID, sql::primary_key()),
			sql::make_column("Player1", &Game::SetPlayerName<0>, &Game::GetPlayerName<0>),
			sql::make_column("Player2", &Game::SetPlayerName<1>, &Game::GetPlayerName<1>),
			sql::make_column("Player3", &Game::SetPlayerName<2>, &Game::GetPlayerName<2>),
			sql::make_column("Player4", &Game::SetPlayerName<3>, &Game::GetPlayerName<3>),
			sql::make_column("Player1_points", &Game::SetPlayerScore<0>, &Game::GetPlayerPoints<0>),
			sql::make_column("Player2_points", &Game::SetPlayerScore<1>, &Game::GetPlayerPoints<1>),
			sql::make_column("Player3_points", &Game::SetPlayerScore<2>, &Game::GetPlayerPoints<2>),
			sql::make_column("Player4_points", &Game::SetPlayerScore<3>, &Game::GetPlayerPoints<3>)
			)
	); 
}

using StorageForGM = decltype(CreateStorageForGames(""));


class GameManager
{
public:
	GameManager() = default;
	GameManager(const std::string& databaseFileName);
private:
	StorageForGM m_database;
};
