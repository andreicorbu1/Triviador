#pragma once

#include <QWidget>
#include "ui_Game.h"
#include "QuestionWindow.h"
#include "Board.h"
#include "Player.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget* parent = nullptr);
	Game(std::vector<Player>& players, QWidget* parent = nullptr);
    ~Game();

    void paintEvent(QPaintEvent* paintEvent);
    void resizeEvent(QResizeEvent * event);
    
signals:
	void finished();
    
private:
    void ShowQuestion(QuestionType type);
    void LoadBackgroundImage();
    void ConnectButtons();

private slots:
    void on_exitButton_clicked();
    void action();

private:
    const uint16_t rectangularSize = 175;
    const uint16_t xPosition = 150;
    const uint16_t yPosition = 25;

private:
    Ui::GameClass ui;
    QuestionWindow m_questionWindow;
    QPixmap m_background;
    Board m_board;
    std::vector<Player> m_players;
    int m_rounds;
};
