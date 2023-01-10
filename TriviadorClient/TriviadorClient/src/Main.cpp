#include "Registration.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	Registration r;
	r.show();
	
    return QApplication::exec();
}
