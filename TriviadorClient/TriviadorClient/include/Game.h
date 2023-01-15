#pragma once
#include "ui_Game.h"
#include <QWidget>
#include <QSignalMapper>
#include <QThread>
#include "ResultWindow.h"
#include "QuestionWindow.h"
#include "Board.h"
#include "Player.h"
#include "../../DLL/User.h"
#include <string>

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget* parent = nullptr);
	Game(std::vector<Player>& players, Player currentPlayer, QWidget* parent = nullptr);
    ~Game();

    void paintEvent(QPaintEvent* paintEvent);
    
signals:
	void finished();
    
private slots:
    void GameLoop();

private slots:
    void on_exitButton_clicked();
    void on_gameFinished();
    void action(int position);

private:
    void ShowQuestion(QuestionType type);
    void SetBackground();
    void ConnectButtons();

    void UpdateBoard();
    void UpdatePlayerScores();
    void AddPlayersHistory();
    void AddPlayerHistory(Player& player, int rank) const;
private:
    const std::pair<uint16_t, uint16_t> playersTableSize = { 200, 75 };
    const std::pair<uint16_t, uint16_t> playersTableStartPoint = { 1280, 50 };

private:
    Ui::GameClass ui;
    QuestionWindow m_questionWindow;
	ResultWindow* m_resultWindow;
    QPixmap m_background;
    QSignalMapper *m_signalMapper;
    int32_t m_ID;

    crow::json::rvalue data;

    Board m_board;
    std::vector<Player> m_players;
	Player m_currentPlayer;
};
