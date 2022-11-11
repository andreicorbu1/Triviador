#include "User.h"

User::User()
{

}

User::User(const std::string& username, const std::string& password):
	m_username(username), m_password(password)
{
	std::cout << "Constructor user apelat!";
}
