#pragma once

#include <QWidget>
#include <QTimer>
#include <QDoubleValidator>
#include <QGraphicsDropShadowEffect>
#include "ui_Question.h"

#include <cpr/cpr.h>
#include <crow.h>

enum class QuestionType
{
    MultipleAnswer,
    NumericalAnswer
};

class Question : public QWidget
{
    Q_OBJECT

public:
    Question(QWidget* parent = nullptr, QuestionType type = QuestionType::MultipleAnswer);
    ~Question();

    void StartTimer();

private slots:
    void UpdateProgressBar();

private:
    void SetShadowEffect();
    void SetTimer();
    void SetQuestionType(QuestionType type);
    void FetchQuestion();
    
private:
    Ui::QuestionClass ui;
    QTimer* m_timer;
};
