#pragma once
#include <cpr/cpr.h>
#include <crow.h>

template <class T>
class Question
{
public:
	virtual cpr::Response GetQuestionFromServer() = 0;
	virtual void CheckIfAnswerIsCorect(T answer) = 0;
};

