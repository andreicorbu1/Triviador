#pragma once
#include "../../DLL/User.h"
#include <regex>
#include <unordered_map>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

static auto CreateStorageForAccounts(const std::string& databaseFileName)
{
	return sql::make_storage(
		databaseFileName,
		sql::make_table(
			"User",
			sql::make_column("id", &User::SetId, &User::GetId, sql::autoincrement(), sql::primary_key()),
			sql::make_column("Username", &User::SetUsername, &User::GetUsername),
			sql::make_column("Password", &User::SetPassword, &User::GetPassword),
			sql::make_column("Level", &User::SetLevel, &User::GetLevel),
			sql::make_column("Points", &User::SetPoints, &User::GetPoints),
			sql::make_column("Games Played", &User::SetGamesPlayed, &User::GetGamesPlayed)
		)
	);
}

using Storage = decltype(CreateStorageForAccounts(""));

class AccountManager
{
public:
	AccountManager() = default;
	AccountManager(const std::string& databaseFileName);
	void AddUser(User& user);
	void DeleteUser(const std::string& username);
	bool SearchUser(const std::string& username) const;
	User GetUser(const std::string& username) const;
	void UpdateUser(const std::string& username, int matchPoints);

private:
	std::unordered_map<std::string, User> m_accounts;
	Storage m_database;
	bool ValidateCredentials(const User& user) const;
};

