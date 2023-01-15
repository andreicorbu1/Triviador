#include "QuestionWindow.h"

QuestionWindow::QuestionWindow(QWidget* parent)
	: QWidget(parent)
{
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	ui.setupUi(this);
	ui_answers = { ui.answer1, ui.answer2, ui.answer3, ui.answer4 };
	ui_flags = { ui.flag1, ui.flag2, ui.flag3, ui.flag4 };
	ui.answerInput->setValidator(new QDoubleValidator(0, 100, 10, this));
	SetConnections();
	SetShadowEffect();
	SetTimer();
}

QuestionWindow::~QuestionWindow()
{
	delete m_timer;
}

void QuestionWindow::SetQuestionType(const QuestionType& type)
{
	m_type = type;
}

void QuestionWindow::SetCurrentPlayer(const Player& player)
{
	m_currentPlayer = player;
}

void QuestionWindow::FetchQuestion(std::vector<Player>& players)
{
	ResetButtons();
	if (m_type == QuestionType::MultipleAnswer)
	{
		this->ui.questionTypes->setCurrentWidget(ui.multiple);
		FetchMultipleAnswerQuestion();
	}
	else if (m_type == QuestionType::NumericalAnswer)
	{
		this->ui.questionTypes->setCurrentWidget(ui.numerical);
		FetchNumericalAnswerQuestion();
	}

	SetEnabledState();
}

void QuestionWindow::FetchMultipleAnswerQuestion()
{
	cpr::Response res = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/getmultiplequestion" },
		cpr::Body{ "username=" + m_currentPlayer.GetName() }
	);
	if (res.status_code == 200)
	{
		auto question = crow::json::load(res.text);
		std::vector<Player> players;
		SetQuestion(question["question"].s());
		SetRightAnswer(question["right_answer"].s());
		SetQuestionId(question["id"].i());

		for (int i = 0; i < kAnswerCount; i++)
		{
			SetAnswer(i, question["answers"][i].s());
		}
		for (auto& player : question["players"])
		{
			auto name = player["name"].s();
			std::string color = player["color"].s();
			Player player(name, Player::ToColor(color));
			players.push_back(player);
		}
		SetFlags(players);
	}
}

void QuestionWindow::FetchNumericalAnswerQuestion()
{
	cpr::Response res = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/getnumericalquestion" },
		cpr::Body{ "username=" + m_currentPlayer.GetName() }
	);
	if (res.status_code == 200)
	{
		auto question = crow::json::load(res.text);
		std::vector<Player> players;
		SetQuestion(question["question"].s());
		SetRightAnswer(question["right_answer"].i());
		for (auto& player : question["players"])
		{
			auto name = player["name"].s();
			std::string color = player["color"].s();
			Player player(name, Player::ToColor(color));
			players.push_back(player);
		}
		SetFlags(players);
		SetQuestionId(question["id"].i());
	}
}

void QuestionWindow::Show()
{
	show();
	m_playerAnswered = false;
	StartTimer();
}

void QuestionWindow::StartTimer()
{
	ui.timeProgressBar->setValue(50);
	if (m_type == QuestionType::MultipleAnswer)
	{
		ui.timeProgressBar->setValue(100);
	}
	m_timer->start(100);
	m_resultTimer.start();
}

QuestionType QuestionWindow::GetQuestionType(const std::string& type)
{
	if (type == "MultipleAnswer")
		return QuestionType::MultipleAnswer;
	else if (type == "NumericalAnswer")
		return QuestionType::NumericalAnswer;
	throw std::runtime_error("Unknown question type");
}

void QuestionWindow::on_hammerButton_clicked()
{
	QString rightAnswer = std::get<std::string>(m_rightAnswer).c_str();
	std::vector<int> indexes(kAnswerCount);
	std::iota(indexes.begin(), indexes.end(), 0);
	std::random_device rd;
	std::mt19937 g(rd());
	std::ranges::shuffle(indexes.begin(), indexes.end(), g);

	int removed = 0;
	for (int i = 0; removed < 2; i++)
	{
		if (ui_answers[indexes[i]]->text() != rightAnswer)
		{
			ui_answers[indexes[i]]->hide();
			removed++;
		}
	}

	ui.hammerButton->close();
}

void QuestionWindow::on_telescopeButton_clicked()
{
	int rightAnswer = std::get<int>(m_rightAnswer);
	int bound = rightAnswer * 0.1 + 2;
	std::unordered_set<int> approximations;

	while (approximations.size() != kAnswerCount)
	{
		int approximation = rightAnswer + QRandomGenerator::global()->bounded(-bound, bound);
		approximations.insert(approximation);
	}

	int i = 0;
	for (auto& approximation : approximations)
	{
		auto telescopeAnswer = new QPushButton(QString::number(approximation), this);
		telescopeAnswer->setGeometry(200, 180 + 60 * (i + 1), 400, 50);
		telescopeAnswer->setStyleSheet("background-image: url(:/Others/question/Plank.svg);\nborder: none;\ncolor: #ffffff;\n");
		telescopeAnswer->setCursor(Qt::PointingHandCursor);
		telescopeAnswer->setText(QString::number(approximation));
		telescopeAnswer->show();

		connect(telescopeAnswer, &QPushButton::clicked, this, [this, approximation]() {
			this->ui.answerInput->setText(QString::number(approximation));
			});

		ui_telescopeAnswers.push_back(telescopeAnswer);
		i++;
	}

	ui.telescopeButton->close();
}

void QuestionWindow::on_parrotButton_clicked()
{
	int rightAnswer = std::get<int>(m_rightAnswer);
	int bound = rightAnswer * 0.1 + 1;
	int approximation = rightAnswer + QRandomGenerator::global()->bounded(-bound, bound);
	ui.answerInput->setText(QString::number(approximation));
	ui.parrotButton->close();
}

void QuestionWindow::on_answerButton_clicked()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	button->setChecked(true);
	setEnabled(false);
	m_playerAnswered = true;
	SendAnswer(button->text().toUtf8().constData());
}

void QuestionWindow::on_submitButton_clicked()
{
	setEnabled(false);
	m_playerAnswered = true;
	SendAnswer(ui.answerInput->text().toUtf8().constData());
}

void QuestionWindow::UpdateProgressBar()
{
	if (ui.timeProgressBar->value() == 0)
	{
		m_timer->stop();
		ShowResults();
		return;
	}

	ui.timeProgressBar->setValue(ui.timeProgressBar->value() - 1);
	m_timer->start(100);
}

void QuestionWindow::SetShadowEffect()
{
	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
	shadow->setBlurRadius(4);
	shadow->setOffset(0, 4);
	shadow->setColor(QColor(0, 0, 0, 25));

	for (auto& answer : ui_answers)
		answer->setGraphicsEffect(shadow);
	ui.plank->setGraphicsEffect(shadow);
}

void QuestionWindow::SetTimer()
{
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(UpdateProgressBar()));
}

void QuestionWindow::SetQuestion(const std::string& question)
{
	this->ui.question->setText(QString::fromUtf8(question));
}

void QuestionWindow::SetAnswer(int index, const std::string& answer)
{
	ui_answers[index]->setText(QString::fromUtf8(answer));
}

void QuestionWindow::SetRightAnswer(const std::string& answer)
{
	m_rightAnswer = answer;
}

void QuestionWindow::SetRightAnswer(const int& answer)
{
	m_rightAnswer = answer;
}

void QuestionWindow::SetQuestionId(const int& id)
{
	m_questionId = id;
}

void QuestionWindow::SetConnections()
{
	for (size_t i = 0; i < ui_answers.size(); i++)
	{
		QObject::connect(ui_answers[i], SIGNAL(pressed()), this, SLOT(on_answerButton_clicked()));
		SetButtonsProperties(i);
	}
}

void QuestionWindow::SetButtonsProperties(int i)
{
	ui_answers[i]->setCheckable(true);
}

void QuestionWindow::SetFlags(std::vector<Player>& players)
{
	HideAllFlags();

	QString baseStyle = "color: #ffffff;\npadding: 15px;\nbackground-repeat: no-repeat;\nbackground-position: center;\n";
	for (int i = 0; i < players.size(); i++)
	{
		QString color = Player::ToString(players[i].GetColor()).c_str();
		ui_flags[i]->setText(QString::fromUtf8(players[i].GetName()));
		ui_flags[i]->setStyleSheet(baseStyle + "background-image: url(:/Flags/question/" + color + "Flag.svg);");
		ui_flags[i]->show();
	}
}

void QuestionWindow::SetEnabledState()
{
	// Disables all buttons if the current player should not answer to the current question
	setEnabled(false);
	for (const auto* flag : ui_flags)
	{
		if (flag->text() == m_currentPlayer.GetName().c_str())
		{
			setEnabled(true);
			break;
		}
	}
}

void QuestionWindow::HideAllFlags() const
{
	for (QLabel* flag : ui_flags)
	{
		flag->hide();
	}
}

void QuestionWindow::ResetButtons()
{
	for (auto* button : ui_answers)
	{
		button->setStyleSheet("color: #ffffff;\nbackground-color: rgb(83, 66, 50);\nchecked: {background-color: rgb(255, 244, 160)}; ");
		button->setChecked(false);
		button->show();
	}

	ui.answerInput->setText("");
	ui.answerInput->setStyleSheet("border: none;\nbackground-color: #725C48;\ncolor: #ffffff;\npadding: 5px;");
	for (auto* button : ui_telescopeAnswers)
	{
		button->close();
	}
	ui_telescopeAnswers.clear();
}

void QuestionWindow::ShowResults() {
	QTimer::singleShot(3000, this, SLOT(close()));
	
	if (!m_playerAnswered) {
		SendAnswer();
	}

	if (m_type == QuestionType::MultipleAnswer)
	{
		for (auto& answer : ui_answers)
		{
			if (answer->text() == std::get<std::string>(m_rightAnswer).c_str())
			{
				answer->setStyleSheet("background: #4D8620;\nborder: none;\ncolor: #ffffff;\n");
			}
			else if (answer->isChecked())
			{
				answer->setStyleSheet("background: #B52828;\nborder: none;\ncolor: #ffffff;\n");
			}
		}
	}
	else if (m_type == QuestionType::NumericalAnswer)
	{
		ui.answerInput->setText("Right answer: " + QString::number(std::get<int>(m_rightAnswer)));
		ui.answerInput->setStyleSheet("background: #4D8620;\nborder: none;\ncolor: #ffffff;\n");
	}
}

void QuestionWindow::SendAnswer(std::string answer)
{
	auto responseTime = static_cast<int>(m_resultTimer.elapsed());
	std::string username = m_currentPlayer.GetName();
	std::string type = m_type == QuestionType::MultipleAnswer ? "multiple" : "numerical";
	
	if (m_type == QuestionType::NumericalAnswer && answer == "")
	{
		answer = "0";
	}
	else if (m_type == QuestionType::MultipleAnswer && answer == "")
		answer = "232";

	cpr::Response res = cpr::Get(cpr::Url{ "http://localhost:18080/sendanswer/" + type },
			cpr::Body{ "username=" + username + "&id=" + std::to_string(m_questionId) + "&answer=" + answer + "&responseTime=" + std::to_string(responseTime) });

	if (res.status_code != 200)
	{
		qDebug() << "Error sending answer";
	}
}