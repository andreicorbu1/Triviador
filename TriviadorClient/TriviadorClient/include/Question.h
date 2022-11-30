#pragma once

#include <QWidget>
#include "ui_Question.h"

class Question : public QWidget
{
    Q_OBJECT

public:
    Question(QWidget *parent = nullptr);
    ~Question();

private:
    Ui::QuestionClass ui;
};
