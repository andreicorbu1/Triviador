#include "Registration.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    
    QApplication a(argc, argv);
    
    Registration registration;
    registration.show();
    
    return QApplication::exec();
}
