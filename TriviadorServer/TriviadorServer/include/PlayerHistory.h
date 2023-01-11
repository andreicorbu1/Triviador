#pragma once
#include<Player.h>
class PlayerHistory
{
public:
	PlayerHistory() = default;
	PlayerHistory(const Player& player, int32_t gameID);

	//Setters:
	void SetUsername(const std::string& username);
	void SetScore(int score);
	void SetRank(size_t rank);
	void SetID(int id);
	//Getters:
	std::string GetUsername() const;
	int GetScore() const;
	size_t GetRank() const;
	int GetID() const;
private:
	int32_t m_ID;
	std::string m_username;
	int m_score;
	size_t m_rank;
};

