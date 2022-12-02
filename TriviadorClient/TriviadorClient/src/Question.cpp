#include "Question.h"

Question::Question(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // Make it WindowModal later
    ui.setupUi(this);
    ui.question->setText("What is the capital of Romania?");
    ui.answer1->setText("Bucharest");
    ui.answer2->setText("Paris");
    ui.answer3->setText("London");
    ui.answer4->setText("Berlin");
    
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
    m_timer->start(100);
}

Question::~Question()
{}

void Question::updateProgressBar()
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