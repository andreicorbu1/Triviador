#pragma once
#include "Question.h"
#include <string>

class MultipleAnswerQuestion: 
	public Question<std::string>
{
public:
	MultipleAnswerQuestion();
	bool CheckIfAnswerIsCorect(const std::string& answer);
	std::string GetQuestion();
	template <size_t index>
	std::string GetAnswer() const;

private:
	void ParseFromJson();
	std::vector<std::string>m_answers;
	static const size_t kNumberOfAnswers = 4;
	cpr::Response GetQuestionFromServer();
};

template<size_t index>
inline std::string MultipleAnswerQuestion::GetAnswer() const
{
	return m_answers[index];
}
