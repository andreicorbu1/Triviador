#include "AccountsManager.h"
#include "User.h"

int main() {
	User user("2cristianciortea", "123456sadS@");
	User user2("3cristianciortea", "123456Dsa");
	User user3("4cristianciortea", "12345621as");
	User user4("5cristianciortea", "123456#");
	User user5("6cristianciortea", "12345aSs@6");
	user.SetGamesPlayed(2);
	AccountManager playerList;
	playerList.AddUser(user);
	playerList.AddUser(user2);
	playerList.AddUser(user3);
	playerList.AddUser(user4);
	playerList.AddUser(user5);
	std::cout << playerList;
	return 0;
}