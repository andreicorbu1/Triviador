#include <filesystem>
#include <iostream>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;
#include "Question.hpp"
#include "MultipleAnswerQuestion.h"
#include "NumericalAnswerQuestion.h"


int main()
{
    std::cout << "Hello World!\n";
    Question<std::string>* question;
    Question<int>* question2;
    MultipleAnswerQuestion maq;
    NumericalAnswerQuestion naq;
    std::cin >> maq;
    std::cin >> naq;
    question = new MultipleAnswerQuestion(maq);
    question2 = new NumericalAnswerQuestion(naq);
    std::cout << maq;
    std::cout << naq;
}
