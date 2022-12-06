#pragma once

#include <QWidget>
#include "ui_Game.h"

#include "QuestionManager.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget* mainMenu = nullptr);
    ~Game();
    
private slots:
    void on_exitButton_clicked();

private:
    Ui::GameClass ui;
    QWidget* m_mainMenu;
    QuestionManager* m_questionManager;
};
