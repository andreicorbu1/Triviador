#pragma once
#ifdef TRIVIADORCOMMON_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#include <string>
class DLL_API User
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
	int m_id = -1;
	std::string m_username;
};