#pragma once

#ifdef TRIVIADORCOMMON_EXPORTS
#define TRIVIADORCOMMON_API __declspec(dllexport)
#else
#define TRIVIADORCOMMON_API __declspec(dllimport)
#endif // TRIVIADORCOMMON_EXPORTS


#include <string>

class TRIVIADORCOMMON_API User
{
public:
	User() = default;
	User(const std::string& username);

	//Setters
	void SetUsername(const std::string& username);
	void SetId(int id);

	//Getters
	std::string GetUsername() const;
	int GetId() const;
private:
	int m_id;
	std::string m_username;
};