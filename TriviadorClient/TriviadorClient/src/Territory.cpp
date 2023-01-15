#include "Territory.h"

Territory::Territory(QWidget* parent)
	:m_owner(Player()),
	m_score(kTerritoryScore),
    m_button(QSharedPointer<QPushButton>(new QPushButton(parent)))
{
    // empty
}

Territory::Territory(const Territory& territory)
{
    *this = territory;
}

Territory::Territory(Territory&& territory) noexcept
{
    *this = std::move(territory);
}

void Territory::SetGeometry(int x, int y, int width, int height)
{
	m_button->setGeometry(x, y, width, height);
}

void Territory::SetMask(const QPixmap& mask)
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

QSharedPointer<QPushButton> Territory::GetButton() const
{
    return m_button;
}

Player Territory::GetOwner() const
{
    return m_owner;
}

void Territory::Update()
{
	if (m_owner.GetColor() == Player::Color::None)
        return;
    
    QString color = m_owner.GetRgbColor();
	m_button->setText(QString::number(m_score));
	m_button->setStyleSheet("background-color: " + color + "; color: white; font: 12pt \"Franklin Gothic Heavy\"; text-align:center;");
}

Territory& Territory::operator=(const Territory& territory)
{
    m_owner = territory.m_owner;
    m_score = territory.m_score;
	m_button = QSharedPointer<QPushButton>(new QPushButton(territory.m_button->parentWidget()));
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