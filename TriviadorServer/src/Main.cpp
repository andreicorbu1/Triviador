#include <filesystem>
#include <iostream>
#include <memory>
#include "User.h"
#include "AccountsManager.h"

void PopulateStorage(Storage& db)
{
	User user("aimon", "ParolaMeaSecreta2@");
	std::vector<User> users;
	for (int i = 0; i < 5; ++i)
	{
		user.SetUsername(user.GetUsername() + std::to_string(i));
		users.emplace_back(user);
	}
	db.insert_range(users.begin(), users.end());
}

int main()
{
	User user("aimon", "ParolaMeaSecreta@");
	Storage db = CreateStorage("Accounts.sqlite");
	db.sync_schema();
	PopulateStorage(db);
	AccountManager test("Accounts.sqlite");
	std::cout << test << "\n";
	//PopulateStorage(db);
	std::cout << db.count<User>();
	return 0;
}
