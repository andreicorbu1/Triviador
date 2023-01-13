#include "Territory.h"


Territory::Territory(QWidget* parent)
	:m_owner(Player()),
	m_score(kTerritoryScore)
{
	m_button = new QPushButton(parent);

}

void Territory::setGeometry(int x, int y, int width, int height)
{
	m_button->setGeometry(x, y, width, height);
}

void Territory::setMask(const QPixmap& mask)
{
    m_button->setCursor(QCursor(Qt::PointingHandCursor));
    m_button->setMask(mask.scaled(m_button->size()).mask());
}

void Territory::SetOwner(const Player& player)
{
	m_owner = player;
}

void Territory::SetScore(const int& score)
{
    m_score = score;
}

QPushButton* Territory::getButton() const
{
    return m_button;
}

void Territory::Update()
{
    QString color = Player::ToString(m_owner.GetColor()).c_str();
    if (color == "None")
        return;

	m_button->setText(QString::number(m_score));
	m_button->setStyleSheet("background-color: " + color + "; color: white; font: 12pt \"Franklin Gothic Heavy\"; text-align:center;");
}

Territory::Territory(const Territory& territory)
{
    *this = territory;
}

Territory::Territory(Territory&& territory) noexcept
{
    *this = std::move(territory);
}

Territory::~Territory()
{
    delete m_button;
}

Territory& Territory::operator=(const Territory& territory)
{
    m_owner = territory.m_owner;
    m_score = territory.m_score;
    m_button = new QPushButton(territory.m_button->parentWidget());
    return *this;
}

Territory& Territory::operator=(Territory&& territory) noexcept
{
    m_owner = territory.m_owner;
    m_score = territory.m_score;
    m_button = territory.m_button;
    new(&territory)Territory;
    return *this;
}