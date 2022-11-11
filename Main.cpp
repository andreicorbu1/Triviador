#include <iostream>
#include "User.h"

int main() {
	User user("cristianciortea", "123456");
	user.SetGamesPlayed(2);
	user.SetPassword("alabalaportocala");
	std::cout << user.GetPassword() << std::endl;
	std::cout << user.GetUsername() << std::endl;
	std::cout << user.GetGamesPlayed();
	return 0;
}