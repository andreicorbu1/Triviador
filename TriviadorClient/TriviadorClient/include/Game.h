#pragma once

#include <QWidget>
#include "ui_Game.h"

#include "QuestionWindow.h"
#include "Board.h"
#include "Player.h"
#include "NumericalAnswerQuestion.h"

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
    
private:
    void ShowQuestion(QuestionType type);

private slots:
    void on_exitButton_clicked();


private:
    const uint16_t rectangularSize = 175;
    const uint16_t xPosition = 150;
    const uint16_t yPosition = 25;

private:
    Ui::GameClass ui;
    QWidget* m_mainMenu;
    QuestionWindow m_questionWindow;
    QPixmap m_pixmap;

    Board m_board;
    std::vector<Player> m_players;
    int m_gameRounds;
};
