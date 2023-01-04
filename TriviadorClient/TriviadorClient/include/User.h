#pragma once
#include <string>

class User
{
public:
	User() = default;
	User(const std::string& username);

	//Setters
	void SetUsername(const std::string& username);
	void SetId(int id);

	//Getters
	std::string GetUsername() const;
	int GetId() const;
private:
	int m_id;
	std::string m_username;
};