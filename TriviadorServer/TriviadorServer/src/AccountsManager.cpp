#include "AccountsManager.h"
AccountManager::AccountManager(const std::string& databaseFileName) : m_database(CreateStorage(databaseFileName))
{
	m_database.sync_schema();
	auto initUsersCount = m_database.count<User>();
	if (initUsersCount > 0)
	{
		auto allUsers = m_database.get_all<User>();
		for (auto& user : allUsers)
		{
			m_accounts.emplace(user.GetUsername(), user);
		}
	}
}

void AccountManager::AddUser(User& user)
{
	if (ValidateCredentials(user))
	{
		auto id = m_database.insert(user);
		user.SetId(id);
		m_accounts[user.GetUsername()] = user;
	}
}

void AccountManager::DeleteUser(const std::string& username)
{
	if (SearchUser(username))
	{
		m_database.remove<User>(m_accounts[username].GetId());
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

void AccountManager::UpdateUser(const std::string& username, int matchPoints)
{
	if (SearchUser(username) == true)
	{
		m_accounts[username].UpdateLevel(matchPoints);
		m_database.update(m_accounts[username]);
	}
}

bool AccountManager::ValidateCredentials(const User& user) const
{
	if (std::regex_match(user.GetPassword(), std::regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,25}$")))
	{
		return SearchUser(user.GetUsername()) == false;
	}
	return false;
}
