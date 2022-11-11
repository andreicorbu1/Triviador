#include "User.h"

User::User(const std::string& username, const std::string& password):
	m_username(username), m_password(password)
{
	m_level = 0;
	m_gamesPlayed = 0;
}

void User::SetUsername(const std::string& username)
{
	m_username = username;
}

void User::SetPassword(const std::string& password)
{
	m_password = password;
}

void User::SetLevel(int level)
{
	m_level = level;
}

void User::SetGamesPlayed(int gamesPlayed)
{
	m_gamesPlayed = gamesPlayed;
}

const std::string User::GetUsername() const
{
	return m_username;
}

const std::string User::GetPassword() const
{
	return m_password;
}

int User::GetLevel() const
{
	return m_level;
}

int User::GetGamesPlayed() const
{
	return m_gamesPlayed;
}
