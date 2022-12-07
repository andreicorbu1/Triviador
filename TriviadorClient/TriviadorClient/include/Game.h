#pragma once

#include <QWidget>
#include "ui_Game.h"

#include "QuestionWindow.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget* mainMenu = nullptr);
    ~Game();
    
private:
    void ShowQuestion(QuestionType type);

private slots:
    void on_exitButton_clicked();

private:
    Ui::GameClass ui;
    QWidget* m_mainMenu;
    QuestionWindow m_questionWindow;
};
