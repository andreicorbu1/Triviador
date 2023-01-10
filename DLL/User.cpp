#include "User.h"

User::User(const std::string& username) : m_username(username)
{
}

void User::SetUsername(const std::string& username)
{
	m_username = username;
}

void User::SetId(int id)
{
	m_id = id;
}

std::string User::GetUsername() const
{
	return m_username;
}

int User::GetId() const
{
	return m_id;
}

