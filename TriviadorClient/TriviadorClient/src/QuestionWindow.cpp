#include "QuestionWindow.h"

QuestionWindow::QuestionWindow(QWidget* parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui.setupUi(this);
    ui_answers = { ui.answer1, ui.answer2, ui.answer3, ui.answer4 };
    ui.answerInput->setValidator(new QDoubleValidator(0, 100, 10, this));
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

void QuestionWindow::FetchQuestion()
{
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
}

void QuestionWindow::FetchMultipleAnswerQuestion()
{
    cpr::Response res = cpr::Get(cpr::Url{ "http://localhost:18080/MultipleAnswerQuestion" });
    if (res.status_code == 200)
    {
        auto question = crow::json::load(res.text);
        SetQuestion(question["question"].s());
        SetRightAnswer(question["right_answer"].s());
        
        for (int i = 0; i < kAnswerCount; i++)
        {
            SetAnswer(i, question["answers"][i].s());
        }
    }
}

void QuestionWindow::FetchNumericalAnswerQuestion()
{
    cpr::Response res = cpr::Get(cpr::Url{ "http://localhost:18080/NumericalAnswerQuestion" });
    if (res.status_code == 200)
    {
        auto question = crow::json::load(res.text);
        SetQuestion(question["question"].s());
        SetRightAnswer(question["right_answer"].i());
    }
}

void QuestionWindow::Show()
{
    this->show();
    StartTimer();
}

void QuestionWindow::StartTimer()
{
    ui.timeProgressBar->setValue(100);
    m_timer->start(100);
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
    std::array<QPushButton*, kAnswerCount> answers{};
    for (auto& approximation : approximations)
    {
        answers[i] = new QPushButton(QString::number(approximation), this);
        answers[i]->setGeometry(200, 180 + 60 * (i + 1), 400, 50);
        answers[i]->setStyleSheet("background-image: url(:/Others/question/Plank.svg);\nborder: none;\ncolor: #ffffff;\n");
        answers[i]->setCursor(Qt::PointingHandCursor);
        answers[i]->setText(QString::number(approximation));
        answers[i]->show();
        
        connect(answers[i], &QPushButton::clicked, this, [this, approximation]() {
            this->ui.answerInput->setText(QString::number(approximation));
        });
        
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

void QuestionWindow::UpdateProgressBar()
{
    if (ui.timeProgressBar->value() == 0)
    {
        m_timer->stop();
        close();
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
