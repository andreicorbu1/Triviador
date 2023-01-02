#include "Board.h"

Board::Board()
	: m_width(0)
	, m_height(0)
	, m_size(0)
	//, m_board(m_size, Territory())
{
	// empty

}

Board::Board(const std::size_t& width, const std::size_t& height, QWidget* parent)
	: m_width(width)
	, m_height(height)
	, m_size(m_width* m_height)
	, m_board(m_size, Territory(parent))
{
	// empty
}

Board::Board(const Board& other)
{
	*this = other;
}

Board::Board(Board&& other) noexcept
{
	*this = std::move(other);
}

Board::~Board() {
	// empty
}

Territory Board::operator[](Position pos) const
{
	const auto& [line, column] = pos;

	if (line >= m_height || column >= m_width) {
		throw std::out_of_range("Position is out of range!");
	}

	return m_board[line * m_width + column];
}

Territory Board::operator[](int pos) const
{
	if (pos < 0 || pos >= m_board.size())
	{
		throw std::out_of_range("Position is out of range!");
	}
	return m_board[pos];
}

Territory& Board::operator[](int pos)
{
	if (pos < 0 || pos >= m_board.size())
	{
		throw std::out_of_range("Position is out of range!");
	}
	return m_board[pos];
}

Board& Board::operator=(const Board& other)
{
	this->m_board = other.m_board;
	this->m_height = other.m_height;
	this->m_width = other.m_width;
	return *this;
}

Board& Board::operator=(Board&& other) noexcept
{
	this->m_board = std::move(other.m_board);
	this->m_height = std::move(other.m_height);
	this->m_width = std::move(other.m_width);
	new(&other) Board;
	return *this;
}

void Board::Set2PGame()
{
	SetGeometry2PGame();
	SetMasks(2);
}

void Board::Set3PGame()
{
	SetMasks(3);
}

void Board::Set4PGame()
{
	SetGeometry4PGame();
	SetMasks(4);
}

int Board::Size()
{
	return m_board.size();
}

void Board::SetMasks(int playersNumber)
{
	QString imageLocation = "../TriviadorClient/resource/map";
	switch (playersNumber)
	{
	case 2:
		imageLocation += QString::number(2);
		break;
	case 3:
		imageLocation += QString::number(3);
		break;
	case 4:
		imageLocation += QString::number(4);
		break;
	default:
		break;
	}
	imageLocation += "players/";
	for (size_t line = 0; line < m_height; line++)
	{
		for (size_t column = 0; column < m_width; column++)
		{
			QString auxLocation = imageLocation;
			auxLocation += QString::number(line) + QString::number(column) + ".png";
			m_board[line * m_width + column].setMask(QPixmap(auxLocation));
			m_board[line * m_width + column].SetButtonProperties();
		}
	}
}

void Board::SetGeometry2PGame()
{
	m_board[0].setGeometry(357, 155, 341, 232);
	m_board[1].setGeometry(610, 172, 218, 220);
	m_board[2].setGeometry(802, 133, 245, 255);
	m_board[3].setGeometry(228, 332, 377, 214);
	m_board[4].setGeometry(576, 364, 254, 193);
	m_board[5].setGeometry(794, 352, 253, 203);
	m_board[6].setGeometry(283, 502, 450, 276);
	m_board[7].setGeometry(586, 522, 300, 264);
	m_board[8].setGeometry(805, 517, 396, 255);
}

void Board::SetGeometry4PGame()
{
	m_board[0].setGeometry(406, 153, 188, 120);
	m_board[1].setGeometry(586, 172, 113, 137);
	m_board[2].setGeometry(689, 170, 144, 112);
	m_board[3].setGeometry(818, 131, 187, 161);
	m_board[4].setGeometry(356, 266, 215, 86);
	m_board[5].setGeometry(458, 275, 219, 112);
	m_board[6].setGeometry(610, 273, 203, 115);
	m_board[7].setGeometry(802, 270, 250, 119);
	m_board[8].setGeometry(316, 334, 130, 98);
	m_board[9].setGeometry(417, 333, 191, 127);
	m_board[10].setGeometry(598, 362, 236, 107);
	m_board[11].setGeometry(800, 352, 251, 95);
	m_board[12].setGeometry(226, 421, 219, 86);
	m_board[13].setGeometry(421, 439, 174, 111);
	m_board[14].setGeometry(577, 433, 243, 119);
	m_board[15].setGeometry(791, 425, 251, 124);
	m_board[16].setGeometry(285, 504, 256, 164);
	m_board[17].setGeometry(439, 521, 253, 121);
	m_board[18].setGeometry(586, 523, 280, 121);
	m_board[19].setGeometry(808, 518, 393, 116);
	m_board[20].setGeometry(463, 635, 122, 129);
	m_board[21].setGeometry(549, 633, 185, 147);
	m_board[22].setGeometry(700, 633, 187, 151);
	m_board[23].setGeometry(874, 593, 325, 179);
}

Territory& Board::operator[](Position pos)
{
	const auto& [line, column] = pos;

	if (line >= m_height || column >= m_width) {
		throw std::out_of_range("Position is out of range!");
	}

	return m_board[line * m_width + column];
}

//std::ostream& operator<<(std::ostream& out, const Board& board)
//{
//	Board::Position pos;
//	auto& [line, column] = pos;
//	for (line = 0; line < board.m_height; line++) {
//		for (column = 0; column < board.m_width; column++) {
//			out << board[pos];
//			out << "  ";
//		}
//		out << "\n\n";
//	}
//
//	return out;
//}