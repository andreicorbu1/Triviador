#pragma once
#include <filesystem>
#include <iostream>
#include <memory>
#include <sqlite_orm/sqlite_orm.h>
#include "MultipleAnswerQuestion.h"
#include "NumericalAnswerQuestion.h"
#include <fstream>
#include <string>
namespace sql = sqlite_orm;

struct QuestionsIntoDataBase
{
public:
	QuestionsIntoDataBase() = default;
	auto createStorage(const std::string& databaseFileName, const MultipleAnswerQuestion& multipleAnswerQuestion);
	auto createStorage(const std::string& databaseFileName, const NumericalAnswerQuestion& numericalAnswerQuestion);
};

