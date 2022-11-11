#pragma once
#include<string>
#include<iostream>

class User
{
private:
	std::string m_username;
	std::string m_password;
public:
	User();
	User(const std::string& username, const std::string& password);
};

