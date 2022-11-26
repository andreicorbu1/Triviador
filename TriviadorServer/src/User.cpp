#include "User.h"

User::User(const std::string& username, const std::string& password) :
	m_username(username), 
	m_password(password)
{
	m_level = 0;
	m_gamesPlayed = 0;
	m_points = 0;
	m_ID = -1;
}

User::User(User&& user)
{
	*this = std::move(user);
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

void User::AddPoints(int points)
{
	m_points += points;
}

User& User::operator=(User&& user)
{
	if (this != &user)
	{
		m_username = user.m_username;
		m_password = user.m_password;
		m_level = user.m_level;
		m_gamesPlayed = user.m_gamesPlayed;
		m_points = user.m_points;
		m_ID = user.m_ID;
		new(&user)User;
	}
	return *this;
}

void User::UpdateLevel(int matchPoints)
{
	AddPoints(matchPoints);
	m_level = m_points / 1000;
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

int User::GetPoints() const
{
	return m_points;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << "Username: " << user.m_username << std::endl;
	os << "Password: " << user.m_password << std::endl;
	os << "Games played: " << user.m_gamesPlayed << std::endl;
	os << "Level: " << user.m_level << std::endl;

	return os;
}
