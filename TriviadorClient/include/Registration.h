#pragma once

#include <QWidget>
#include "ui_Registration.h"

class Registration : public QWidget
{
    Q_OBJECT

public:
    Registration(QWidget *parent = nullptr);
    ~Registration();
    
    bool isRegistered() const;

private:
    Ui::RegistrationClass ui;
    bool m_isRegistered = true;
};
