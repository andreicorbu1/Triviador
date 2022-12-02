#pragma once

#include <QWidget>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include "ui_Question.h"

#include <cpr/cpr.h>
#include <crow.h>

class Question : public QWidget
{
    Q_OBJECT

public:
    Question(QWidget *parent = nullptr);
    ~Question();

private slots:
    void UpdateProgressBar();

private:
    Ui::QuestionClass ui;
    QTimer* m_timer;
    
    void SetShadowEffect();
    void SetTimer();
    void FetchQuestion();
};
