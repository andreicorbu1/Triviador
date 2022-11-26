#include <filesystem>
#include <iostream>
#include <memory>
#include <sqlite_orm/sqlite_orm.h>
#include "User.h"
#include "AccountsManager.h"
namespace sql = sqlite_orm;
auto createStorage(const std::string& databaseFileName)
{
	return sql::make_storage(
		databaseFileName,
		sql::make_table(
		"User",	
		sql::make_column("id", &User::m_ID, sql::autoincrement(), sql::primary_key()),
		sql::make_column("Username", &User::m_username),
		sql::make_column("Password", &User::m_password),
		sql::make_column("Level", &User::m_level),
		sql::make_column("Points", &User::m_points),
		sql::make_column("Games Played", &User::m_gamesPlayed)
	)
	);
}

using Storage = decltype(createStorage(""));

void PopulateStorage(Storage& db)
{
	User user("aimon", "ParolaMeaSecreta2@");
	std::vector<User> users;
	for (int i = 0; i < 5; ++i)
	{
		users.emplace_back(user);
	}
	db.insert_range(users.begin(), users.end());
}

int main()
{
	User user("aimon", "ParolaMeaSecreta@");
	Storage db = createStorage("Accounts.sqlite");
	db.sync_schema();
	PopulateStorage(db);
	std::cout << db.count<User>();
	return 0;
}
