#include "Lobby.h"

Lobby::Lobby(QWidget *parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);
}

Lobby::~Lobby()
{}

void Lobby::paintEvent(QPaintEvent * paintEvent)
{
	QPainter painter(this);
	QRect rect(50, 50, 50, 50);
	painter.drawRect(rect);
}
