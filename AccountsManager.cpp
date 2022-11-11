#include "AccountsManager.h"

void AccountManager::AddUser(const User& user)
{
	if (ValidateCredentials(user))
	{
		m_accounts[user.GetUsername()] = user;
	}
}

bool AccountManager::ValidateCredentials(const User& user) const
{
	if (std::regex_match(user.GetPassword(), std::regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,25}$")))
	{
		return m_accounts.contains(user.GetUsername()) == false;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const AccountManager& manager)
{
	for(auto it : manager.m_accounts)
	{
		os << it.second.GetUsername() << "\n" << it.second.GetPassword() << "\n" << it.second.GetGamesPlayed() << "\n" << it.second.GetLevel() << "\n";
	}
	return os;
}
