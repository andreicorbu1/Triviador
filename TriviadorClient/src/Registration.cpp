#include "Registration.h"

Registration::Registration(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

Registration::~Registration()
{
}

bool Registration::isRegistered() const
{
    return m_isRegistered;
}
