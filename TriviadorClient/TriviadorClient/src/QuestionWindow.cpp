#include "QuestionWindow.h"

QuestionWindow::QuestionWindow(QWidget* parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui.setupUi(this);
    ui.answerInput->setValidator(new QDoubleValidator(0, 100, 10, this));
    SetShadowEffect();
    SetTimer();
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

void QuestionWindow::SetQuestionType(QuestionType type)
{
    switch (type)
    {
    case QuestionType::MultipleAnswer:
        this->ui.questionTypes->setCurrentWidget(ui.multiple);
        break;
    case QuestionType::NumericalAnswer:
        this->ui.questionTypes->setCurrentWidget(ui.numerical);
        break;
    default:
        break;
    }
}


void QuestionWindow::SetQuestion(const std::string& question)
{
    this->ui.question->setText(QString::fromUtf8(question));
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
}

void QuestionWindow::on_telescopeButton_clicked()
{
    // TODO: Implement telescope
}

void QuestionWindow::on_parrotButton_clicked()
{
    // TODO: Implement parrot
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