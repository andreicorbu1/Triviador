#pragma once
#include "ui_QuestionWindow.h"

#include <QDoubleValidator>
#include <QElapsedTimer>
#include <QEventLoop>
#include <QGraphicsDropShadowEffect>
#include <QRandomGenerator>
#include <QTimer>
#include <QWidget>

#include "Player.h"

#include <algorithm>
#include <cpr/cpr.h>
#include <crow.h>
#include <string>
#include <unordered_set>
#include <variant>

enum class QuestionType
{
	MultipleAnswer,
	NumericalAnswer
};

class QuestionWindow : public QWidget
{
	Q_OBJECT

public:
	// Constructors
	QuestionWindow(QWidget* parent = nullptr);
	~QuestionWindow();

	// Setters
	void SetQuestionType(const QuestionType& type);
	void SetCurrentPlayer(const Player& player);

	// Getters
	void FetchQuestion(std::vector<Player>& players);
	void FetchMultipleAnswerQuestion();
	void FetchNumericalAnswerQuestion();

	// Other
	void Show();
	void StartTimer();
	static QuestionType GetQuestionType(const std::string& type);

private slots:
	void on_hammerButton_clicked();
	void on_telescopeButton_clicked();
	void on_parrotButton_clicked();
	// multiple
	void on_answerButton_clicked();
	// numerical
	void on_submitButton_clicked();

	void UpdateProgressBar();
	void ShowResults();
	void SendAnswer(std::string answer = "");

private:
	// Setters
	void SetShadowEffect();
	void SetTimer();
	void SetQuestion(const std::string& question);
	void SetAnswer(int position, const std::string& answer);
	void SetRightAnswer(const std::string& answer);
	void SetRightAnswer(const int& answer);
	void SetQuestionId(const int& id);
	void SetConnections();
	void SetButtonsProperties(int i);
	void SetFlags(std::vector<Player>& players);
	void SetEnabledState();

private:
	void HideAllFlags() const;
	void ResetButtons();

private:
	// Constants
	static const int kAnswerCount = 4;

	// UI elements
	Ui::QuestionWindowClass ui;
	std::array<QPushButton*, kAnswerCount> ui_answers;
	std::array<QLabel*, 4> ui_flags;
	std::vector<QPushButton*> ui_telescopeAnswers;

	// Members
	QTimer* m_timer;
	QuestionType m_type;
	std::variant<std::string, int> m_rightAnswer;
	int m_questionId;
	Player m_currentPlayer;
	std::vector<Player> m_players;
	QElapsedTimer m_resultTimer;
	bool m_playerAnswered;
};
