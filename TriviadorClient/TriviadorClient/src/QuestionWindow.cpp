#include "QuestionWindow.h"

QuestionWindow::QuestionWindow(QWidget* parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui.setupUi(this);
    ui.answerInput->setValidator(new QDoubleValidator(0, 100, 10, this));
    SetShadowEffect();
    SetTimer();

    ui_answers = { ui.answer1, ui.answer2, ui.answer3, ui.answer4 };
}

QuestionWindow::~QuestionWindow()
{
    delete m_timer;
}


void QuestionWindow::SetShadowEffect()
{
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(4);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 25));

    ui.answer1->setGraphicsEffect(shadow);
    ui.answer2->setGraphicsEffect(shadow);
    ui.answer3->setGraphicsEffect(shadow);
    ui.answer4->setGraphicsEffect(shadow);
    ui.plank->setGraphicsEffect(shadow);
}

void QuestionWindow::SetTimer()
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(UpdateProgressBar()));
}

void QuestionWindow::SetQuestionType(const QuestionType& type)
{
    m_type = type;
}


void QuestionWindow::SetQuestion(const std::string& question)
{
    this->ui.question->setText(QString::fromUtf8(question));
}

void QuestionWindow::SetAnswer(int index, const std::string& answer)
{
    ui_answers[index]->setText(QString::fromUtf8(answer));
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
    MultipleAnswerQuestion question;
    SetQuestion(question.GetQuestion());
    for (int i = 0; i < kAnswerCount; i++)
        SetAnswer(i, question.GetAnswer(i));
}

void QuestionWindow::FetchNumericalAnswerQuestion()
{
    NumericalAnswerQuestion question;
    SetQuestion(question.GetQuestion());
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
    for (int i = 0; i < 2; i++)
    {
        int random = QRandomGenerator::global()->bounded(4);
        
        switch (random)
        {
        case 0:
            ui.answer1->hide();
            break;
        case 1:
            ui.answer2->hide();
            break;
        case 2:
            ui.answer3->hide();
            break;
        case 3:
            ui.answer4->hide();
            break;  
        default:
            break;
        }
    }

    ui.hammerButton->close();
}

void QuestionWindow::on_telescopeButton_clicked()
{
    ui.telescopeButton->close();
}

void QuestionWindow::on_parrotButton_clicked()
{
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