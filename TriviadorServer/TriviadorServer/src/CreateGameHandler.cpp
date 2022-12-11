#include "CreateGameHandler.h"

CreateGameHandler::CreateGameHandler(std::unordered_map<int32_t, Game> gamesOngoing) : m_gamesOngoing(gamesOngoing)
{}

crow::response CreateGameHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto gameIdIter = bodyArgs.find("id");
	auto numberOfPlayersIter = bodyArgs.find("players");
	if (gameIdIter != end && numberOfPlayersIter != end)
	{
		int numberOfPlayers = std::stoi(numberOfPlayersIter->second);
		switch (numberOfPlayers)
		{
			case 2:
			{
				Game newGame(Player("Player1", Player::Color::Blue), Player("Player2", Player::Color::Green));

				break;
			}
			case 3:
			{
				Game newGame(Player("Player1", Player::Color::Blue), Player("Player2", Player::Color::Green), Player("Player3", Player::Color::Red));
				break;
			}
			case 4:
			{
				Game newGame(Player("Player1", Player::Color::Blue), Player("Player2", Player::Color::Green),
					Player("Player3", Player::Color::Red), Player("Player4", Player::Color::Yellow));
				break;
			}
			default:
			{
				return crow::response(400);
			}
		}
	}
}
