#include "AccountsManager.h"
AccountManager::AccountManager(const std::string& databaseName)
{
	auto allUsers = db.get_all<User>();
	for (auto& user : allUsers)
	{
		m_accounts.emplace(user.GetUsername(), user);
	}
}

void AccountManager::AddUser(User& user)
{
	if (ValidateCredentials(user))
	{
		user.SetID(db.insert(user));
		m_accounts[user.GetUsername()] = user;
	}
}

void AccountManager::DeleteUser(const std::string& username)
{
	if (SearchUser(username))
	{
		m_accounts.erase(username);
	}
}

bool AccountManager::SearchUser(const std::string& username) const
{
	// True if successful, false otherwise
	return m_accounts.contains(username);
}

User AccountManager::GetUser(const std::string& username) const
{
	if (SearchUser(username))
	{
		return m_accounts.at(username);
	}
	return {};
}

void AccountManager::UpdateUser(const User& user)
{
	m_accounts[user.GetUsername()] = user;
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
	//Temporary implementation, waiting for class User << operator override
	for (const auto& it : manager.m_accounts)
	{
		os << it.second << "\n";
	}
	return os;
}
