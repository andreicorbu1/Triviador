#pragma once
#include<Player.h>
class PlayerHistory
{
public:
	PlayerHistory() = default;
	PlayerHistory(const Player& player);

	//Setters:
	void SetUsername(const std::string& username);
	void SetScore(int score);
	void SetRank(size_t rank);
	//Getters:
	std::string GetUsername() const;
	int GetScore() const;
	size_t GetRank() const;
private:
	std::string m_username;
	int m_score;
	size_t m_rank;
};

