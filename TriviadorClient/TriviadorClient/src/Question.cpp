#include "Question.h"

Question::Question(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // Make it WindowModal later
    ui.setupUi(this);
}

Question::~Question()
{}
