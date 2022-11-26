#pragma once
#include "User.h"
#include <regex>
#include <unordered_map>

class AccountManager
{
public:
	AccountManager() = default;
	void AddUser(const User& user);
	void DeleteUser(const std::string& username);
	bool SearchUser(const std::string& username) const;
	User GetUser(const std::string &username) const;
	void UpdateUser(const User& user);
	friend std::ostream& operator << (std::ostream& os, const AccountManager& manager);

private:
	std::unordered_map<std::string, User> m_accounts;
	bool ValidateCredentials(const User& user) const;
};

