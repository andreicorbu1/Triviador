#pragma once
#include "User.h"
#include <regex>
#include <unordered_map>

class AccountManager
{
public:
	AccountManager() = default;
	void AddUser(const User& user);
	friend std::ostream& operator << (std::ostream& os, const AccountManager& manager);

private:
	std::unordered_map<std::string, User> m_accounts;
	bool ValidateCredentials(const User& user) const;
};

