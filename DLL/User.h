#pragma once
#ifdef TRIVIADORCOMMON_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#include<string>
#include<iostream>

class DLL_API User
{
public:
	User() = default;
	User(const std::string& username, const std::string& password = "");
	User(const User& user) = default;
	User(User&& user) noexcept;
	~User() = default;

	//Setters:
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);
	void SetLevel(int level);
	void SetGamesPlayed(int gamesPlayed);
	void SetPoints(int points);
	void SetId(int id);

	//Getters:
	const std::string& GetUsername() const;
	const std::string& GetPassword() const;
	int GetLevel() const;
	int GetGamesPlayed() const;
	int GetPoints() const;
	int GetId() const;

	//Operators:
	User& operator=(const User& user) = default;
	User& operator=(User&& user) noexcept;

	// Other methods:
	void UpdateLevel(int matchPoints);

private:
	void AddPoints(int points);

private:
	int m_id;
	std::string m_username;
	std::string m_password;
	int m_level;
	int m_gamesPlayed;
	int m_points;
};

