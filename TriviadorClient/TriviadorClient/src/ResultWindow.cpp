#include "ResultWindow.h"

ResultWindow::ResultWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

ResultWindow::ResultWindow(std::vector<Player>& players, QWidget* parent)
	: m_players(players)
	, QWidget(parent)
{
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	ui.setupUi(this);
	std::sort(m_players.begin(), m_players.end(), [](const Player& a, const Player& b) { return a.GetScore() > b.GetScore(); });
	update();
}

ResultWindow::~ResultWindow()
{}

void ResultWindow::paintEvent(QPaintEvent* paintEvent)
{
	QPainter painter(this);
	painter.setBrush(QColor(83, 66, 50));
	for (size_t i = 0; i < m_players.size(); i++)
	{
		QString color = Player::ToString(m_players[i].GetColor()).c_str();
		QRect playerTable(playersTableStartPoint.first, playersTableStartPoint.second + (i * (playersTableSize.second + 3)), playersTableSize.first, playersTableSize.second);
		painter.setPen(color);
		painter.drawRect(playerTable);
		QString tableText = (m_players[i].GetName() + " " + std::to_string(m_players[i].GetScore())).c_str();
		painter.setFont(QFont("Franklin Gothic Heavy", 20));
		painter.setPen(Qt::white);
		QRect textRect = painter.boundingRect(playerTable, Qt::AlignCenter, tableText);
		painter.drawText(textRect, Qt::AlignCenter, tableText);
	}
}

void ResultWindow::on_backToMenuButton_clicked()
{
	emit backToMenu();
}