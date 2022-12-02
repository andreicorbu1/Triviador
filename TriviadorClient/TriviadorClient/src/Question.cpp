#include "Question.h"

Question::Question(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // Make it WindowModal later
    ui.setupUi(this);
    SetShadowEffect();
    SetTimer();
    
}

Question::~Question()
{}


void Question::SetShadowEffect()
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

void Question::SetTimer()
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(UpdateProgressBar()));
    m_timer->start(100);
}

void Question::FetchQuestion() {
    cpr::Response r = cpr::Get(cpr::Url{ "http://localhost:18080/question" });
    std::cout << r.text << std::endl;
}

void Question::UpdateProgressBar()
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