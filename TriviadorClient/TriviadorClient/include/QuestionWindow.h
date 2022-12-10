#pragma once

#include <QWidget>
#include <QTimer>
#include <QRandomGenerator>
#include <QDoubleValidator>
#include <QEventLoop>
#include <QGraphicsDropShadowEffect>
#include "ui_QuestionWindow.h"

#include <cpr/cpr.h>
#include <crow.h>

enum class QuestionType
{
    MultipleAnswer,
    NumericalAnswer
};

class QuestionWindow : public QWidget
{
    Q_OBJECT

public:
    QuestionWindow(QWidget* parent = nullptr);
    ~QuestionWindow();


    void SetQuestion(const std::string& question);
    void StartTimer();
    void SetQuestionType(QuestionType type);

private slots:
    void on_hammerButton_clicked();
    void on_telescopeButton_clicked();
    void on_parrotButton_clicked();

    void UpdateProgressBar();

private:
    void SetShadowEffect();
    void SetTimer();
    
private:
    Ui::QuestionWindowClass ui;
    QTimer* m_timer;
};
