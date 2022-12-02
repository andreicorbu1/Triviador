#pragma once

#include <QWidget>
#include "ui_Game.h"

#include "Board.h"
#include "Player.h"
#include "Question.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget* mainMenu = nullptr);
    Game(const Player& player1, const Player& player2, QWidget* mainMenu = nullptr);
    Game(const Player& player1, const Player& player2, const Player& player3, QWidget* mainMenu = nullptr);
    Game(const Player& player1, const Player& player2, const Player& player3, const Player& player4, QWidget* mainMenu = nullptr);
    ~Game();

    void paintEvent(QPaintEvent* paintEvent);
    
private slots:
    void on_exitButton_clicked();


private:
    

private:
    Ui::GameClass ui;
    QWidget* m_mainMenu;
    Question* m_question;

    Board m_board;
    std::vector<Player> m_players;
    int m_gameRounds;
};
