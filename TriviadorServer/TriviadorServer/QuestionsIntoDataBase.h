#pragma once
#include <filesystem>
#include <iostream>
#include <memory>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;
#include "MultipleAnswerQuestion.h"
#include "NumericalAnswerQuestion.h"
#include <fstream>
#include <string>

class QuestionsIntoDataBase
{
public:
	QuestionsIntoDataBase() = default;
	auto createStorage(const std::string& databaseFileName, MultipleAnswerQuestion& multipleAnswerQuestion);
	auto createStorage(const std::string& databaseFileName, const NumericalAnswerQuestion& numericalAnswerQuestion);
};

