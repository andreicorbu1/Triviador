#pragma once

#include <QWidget>
#include "ui_Game.h"
#include "QuestionWindow.h"
#include "Board.h"
#include "Player.h"
#include <QSignalMapper>

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget* parent = nullptr);
	Game(std::vector<Player>& players, QWidget* parent = nullptr);
    ~Game();

    void paintEvent(QPaintEvent* paintEvent);
    
signals:
	void finished();
    
private:
    void ShowQuestion(QuestionType type);
    void SetBackground();
    void ConnectButtons();

private slots:
    void on_exitButton_clicked();
    void action(int position);

private:
    const uint16_t rectangularSize = 175;
    const uint16_t xPosition = 150;
    const uint16_t yPosition = 25;

private:
    Ui::GameClass ui;
    QuestionWindow m_questionWindow;
    QPixmap m_background;
    QSignalMapper *m_signalMapper;
    Board m_board;
    std::vector<Player> m_players;
    int m_rounds;
};
