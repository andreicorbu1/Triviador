#pragma once

#include <QWidget>
#include <QTimer>
#include "ui_Question.h"

class Question : public QWidget
{
    Q_OBJECT

public:
    Question(QWidget *parent = nullptr);
    ~Question();

private slots:
    void updateProgressBar();

private:
    Ui::QuestionClass ui;
    QTimer* m_timer;
};
