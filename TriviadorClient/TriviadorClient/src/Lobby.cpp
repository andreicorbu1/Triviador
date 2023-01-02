#include "Lobby.h"

Lobby::Lobby(std::string lobbyID, QWidget *parent):
	m_lobbyID(lobbyID)
{
	ui.setupUi(this);
	ui.lobbyID_label->setText(QString::fromUtf8("Lobby ID: " + lobbyID));
	setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);
	this->setWindowState(Qt::WindowMaximized);
}

Lobby::~Lobby()
{}

void Lobby::on_leaveLobbyButton_clicked()
{
	emit finished();
}

void Lobby::paintEvent(QPaintEvent * paintEvent)
{
	QPainter painter(this);
	auto res = cpr::Get
		(
			cpr::Url{ "http://localhost:18080/waitinginlobby" },
			cpr::Body{ "id=" + m_lobbyID }
		);
	if (res.status_code == 100)
	{
	}
	else if (res.status_code == 410)
	{
		QMessageBox msgBox;
		msgBox.setText("Lobby waiting time has expired");
		msgBox.exec();
		on_leaveLobbyButton_clicked();
	}
}
