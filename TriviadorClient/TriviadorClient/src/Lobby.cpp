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
	painter.drawRect(QRect(100, 100, 50, 50));
}
