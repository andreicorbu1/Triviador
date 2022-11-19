#pragma once
#include<string>
#include<iostream>

class User
{
public:
	User() = default;
	User(const std::string& username, const std::string& password);

	//Setters:
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);
	void SetLevel(int level);
	void SetGamesPlayed(int gamesPlayed);
	int GetPoints();

	//Getters:
	const std::string GetUsername() const;
	const std::string GetPassword() const;
	int GetLevel() const;
	int GetGamesPlayed() const;

	//Operators:
	friend std::ostream& operator << (std::ostream& os, const User& user);

	void UpdateLevel(int matchPoints);

private:
	void AddPoints(int points);

private:
	std::string m_username;
	std::string m_password;
	int m_level;
	int m_gamesPlayed;
	int m_points;
};

