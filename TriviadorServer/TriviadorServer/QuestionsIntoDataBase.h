#pragma once
#include <filesystem>
#include <iostream>
#include <memory>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;
#include "MultipleAnswerQuestion.h"
#include "NumericalAnswerQuestion.h"
#include <fstream>
class QuestionsIntoDataBase
{
public:
	QuestionsIntoDataBase() = default;
	auto createStorage(const MultipleAnswerQuestion& multipleAnswerQuestion);
	auto createStorage(const NumericalAnswerQuestion& numericalAnswerQuestion);
};

