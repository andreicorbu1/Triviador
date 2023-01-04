#include "Lobby.h"

Lobby::Lobby()
{
	m_availableColors.resize(kNumberOfColors);
	SetAvailableColors();
	//m_lobbyId = GenerateRandomLobbyID();
	std::chrono::duration<int, std::ratio<3*60>>threeMinutes(1);
	m_expirationTime = std::chrono::system_clock::now() + threeMinutes;
}

Lobby::Lobby(const Lobby& lobby)
{
	*this = lobby;
}

Lobby::Lobby(const Player& player)
{
	m_availableColors.resize(kNumberOfColors);
	SetAvailableColors();
	AddPlayer(player);
	m_lobbyId = GenerateRandomLobbyID();
	std::chrono::duration<int, std::ratio<3 * 60>>threeMinutes(1);
	m_expirationTime = std::chrono::system_clock::now() + threeMinutes;
}

Lobby::~Lobby()
{
	ClearLobby();
}

Lobby& Lobby::operator=(const Lobby& lobby)
{
	if (this != &lobby) {
		m_lobbyId = lobby.m_lobbyId;
		m_availableColors = lobby.m_availableColors;
		m_expirationTime = lobby.m_expirationTime;
		m_players = lobby.m_players;
	}
	return *this;
}

void Lobby::AddPlayer(const Player& player)
{
	m_players.push_back(player);
	Player::Color lastColorFromAvailableColors = static_cast<Player::Color>(m_availableColors[m_availableColors.size() - 1]);
	m_players[m_players.size() - 1].SetColor(lastColorFromAvailableColors);
	m_availableColors.pop_back();

	std::chrono::duration<int, std::ratio<60>>oneMinute(1);
	m_expirationTime += oneMinute;
}

bool Lobby::RemovePlayer(const std::string& username)
{
	if (m_players.size() != 0)
	{
		auto it = std::find_if(m_players.begin(), m_players.end(), [&username](const Player& player)
			{
				return player.GetName() == username;
			});
		if (it != m_players.end())
		{
			m_players.erase(it);
			return true;
		}
	}
	return false;
}

void Lobby::ClearLobby()
{
	m_players.clear();
	m_availableColors.clear();
	m_lobbyId = INT_MAX;
}

const Player& Lobby::GetPlayerAt(int index) const
{
	return m_players[index];
}

int Lobby::GetNumberOfPlayers()
{
	return m_players.size();
}

std::vector<Player> Lobby::GetPlayers()
{
	return m_players;
}

uint32_t Lobby::GenerateRandomLobbyID()
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(1000, 9999);

	return dist(rd);
}

int Lobby::GetLobbyID() const
{
	return m_lobbyId;
}

const std::chrono::system_clock::time_point& Lobby::GetExpirationTime() const
{
	return m_expirationTime;
}

void Lobby::SetAvailableColors()
{
	m_availableColors[0] = static_cast<int>(Player::Color::Red);
	m_availableColors[1] = static_cast<int>(Player::Color::Yellow);
	m_availableColors[2] = static_cast<int>(Player::Color::Blue);
	m_availableColors[3] = static_cast<int>(Player::Color::Green);
	std::shuffle(m_availableColors.begin(), m_availableColors.end(), std::default_random_engine{});
}

