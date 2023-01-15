#pragma once
#include "User.h"
#include <regex>
#include <unordered_map>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

static auto CreateStorage(const std::string& databaseFileName)
{
	return sql::make_storage(
		databaseFileName,
		sql::make_table(
		"User",
		sql::make_column("id", &User::m_id, sql::autoincrement(), sql::primary_key()),
		sql::make_column("Username", &User::m_username),
		sql::make_column("Password", &User::m_password),
		sql::make_column("Level", &User::m_level),
		sql::make_column("Points", &User::m_points),
		sql::make_column("Games Played", &User::m_gamesPlayed)
	)
	);
}

using Storage = decltype(CreateStorage(""));

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

