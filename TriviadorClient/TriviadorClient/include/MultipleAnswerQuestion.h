#pragma once
#include "Question.h"
#include <string>

class MultipleAnswerQuestion: 
	public Question<std::string>
{
public:
	MultipleAnswerQuestion();
	
	bool CheckIfAnswerIsCorect(const std::string& answer);
	
	// Getters
	std::string GetQuestion() const;
	std::string GetRightAnswer() const;
	std::string GetAnswer(int index) const;
	
private:
	static const size_t kAnswerCount = 4;
	
	std::array<std::string, kAnswerCount> m_answers;
	
	void ParseFromJson();
	cpr::Response GetQuestionFromServer();
};