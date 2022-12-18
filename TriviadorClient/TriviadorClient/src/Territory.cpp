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
    m_button->setMask(mask.scaled(m_button->size()).mask());
}

void Territory::SetButtonProperties()
{
    m_button->setCursor(QCursor(Qt::PointingHandCursor));
    m_button->setStyleSheet("background-color: blue;");
}

//Territory::Territory(QWidget* parent)
//    : m_score(kBaseScore)
//{
//    //empty
//    m_bu
//}
//
//Territory::Territory(const Player& owner)
//    : m_owner(owner)
//    , m_score(kTerritoryScore)
//{
//    // empty
//}
//
//Territory::Territory(const Player& owner, const bool& isBase)
//    : m_owner(owner)
//    , m_score(kBaseScore)
//{
//    // empty
//}

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

//std::ostream& operator<< (std::ostream& out, const Territory& t)
//{
//    out << (t.m_owner.has_value() ? t.m_owner.value().GetName() : "No owner");
//    out << "[" << t.m_score << "]";
//    return out;
//}