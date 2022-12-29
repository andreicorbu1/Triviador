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
	m_board[0].setGeometry(367, 165, 351, 250);
	m_board[1].setGeometry(627, 182, 228, 235);
	m_board[2].setGeometry(825, 143, 255, 270);
	m_board[3].setGeometry(235, 357, 390, 229);
	m_board[4].setGeometry(593, 389, 264, 203);
	m_board[5].setGeometry(817, 376, 263, 213);
	m_board[6].setGeometry(293, 535, 460, 300);
	m_board[7].setGeometry(602, 559, 310, 280);
	m_board[8].setGeometry(830, 553, 406, 275);

}

void Board::SetGeometry4PGame()
{
	m_board[0].setGeometry(420, 165, 190, 126);
	m_board[1].setGeometry(603, 184, 116, 144);
	m_board[2].setGeometry(709, 182, 148, 120);
	m_board[3].setGeometry(842, 143, 191, 169);
	m_board[4].setGeometry(370, 281, 219, 94);
	m_board[5].setGeometry(475, 290, 223, 125);
	m_board[6].setGeometry(629, 290, 209, 125);
	m_board[7].setGeometry(824, 289, 259, 127);
	m_board[8].setGeometry(327, 357, 134, 106);
	m_board[9].setGeometry(431, 357, 195, 135);
	m_board[10].setGeometry(616, 387, 241, 115);
	m_board[11].setGeometry(823, 374, 257, 105);
	m_board[12].setGeometry(236, 451, 223, 94);
	m_board[13].setGeometry(430, 467, 186, 123);
	m_board[14].setGeometry(592, 462, 253, 130);
	m_board[15].setGeometry(816, 454, 255, 135);
	m_board[16].setGeometry(293, 535, 265, 183);
	m_board[17].setGeometry(451, 555, 264, 138);
	m_board[18].setGeometry(600, 556, 295, 138);
	m_board[19].setGeometry(830, 553, 406, 126);
	m_board[20].setGeometry(475, 678, 130, 139);
	m_board[21].setGeometry(563, 676, 193, 159);
	m_board[22].setGeometry(719, 676, 195, 165);
	m_board[23].setGeometry(898, 636, 335, 189);
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