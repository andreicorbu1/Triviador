#pragma once
#include "User.h"
#include <regex>
#include <unordered_map>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

static auto CreateStorage(const std::string& databaseFileName)
{
	auto db = sql::make_storage(
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
	db.sync_schema();
	return db;
}

using Storage = decltype(CreateStorage(""));

class AccountManager
{
public:
	AccountManager();
	void AddUser(User& user);
	void DeleteUser(const std::string& username);
	bool SearchUser(const std::string& username) const;
	User GetUser(const std::string& username) const;
	void UpdateUser(const User& user);
	friend std::ostream& operator << (std::ostream& os, const AccountManager& manager);

private:
	std::unordered_map<std::string, User> m_accounts;
	Storage db = CreateStorage("resource/Accounts.sqlite");
	bool ValidateCredentials(const User& user) const;
};

