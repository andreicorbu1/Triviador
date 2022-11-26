#pragma once
#include<string>
#include<iostream>

class User
{
public:
	User() = default;
	User(const std::string& username, const std::string& password);
	User(const User& user) = default;
	User(User&& user);
	~User() = default;

	//Setters:
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);
	void SetLevel(int level);
	void SetGamesPlayed(int gamesPlayed);
	void SetID(int ID);

	//Getters:
	const std::string GetUsername() const;
	const std::string GetPassword() const;
	int GetLevel() const;
	int GetGamesPlayed() const;
	int GetPoints() const;

	//Operators:
	User& operator=(const User& user) = default;
	User& operator=(User&& user);
    
	friend auto CreateStorage(const std::string& databaseFileName);
	friend class AccountManager;
	friend std::ostream& operator << (std::ostream& os, const User& user);
    
	// Other methods:
	void UpdateLevel(int matchPoints);

private:
	void AddPoints(int points);

private:
	std::string m_username;
	std::string m_password;
	int m_level;
	int m_gamesPlayed;
	int m_points;
	int m_ID;
};

