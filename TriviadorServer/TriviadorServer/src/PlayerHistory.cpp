#include "PlayerHistory.h"

PlayerHistory::PlayerHistory(const Player& player)
	:m_username(player.GetName())
	,m_score(player.GetScore())
	,m_rank(player.GetRank())
{
	//empty
}

void PlayerHistory::SetUsername(const std::string& username)
{
	m_username = username;
}

void PlayerHistory::SetScore(int score)
{
	m_score = score;
}

void PlayerHistory::SetRank(size_t rank)
{
	m_rank = rank;
}

std::string PlayerHistory::GetUsername() const
{
	return m_username;
}

int PlayerHistory::GetScore() const
{
	return m_score;
}

size_t PlayerHistory::GetRank() const
{
	return m_rank;
}
