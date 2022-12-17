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
	, m_size(m_width * m_height)
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

const Territory& Board::operator[](Position pos) const
{
	const auto& [line, column] = pos;

	if (line >= m_height || column >= m_width) {
		throw std::out_of_range("Position is out of range!");
	}

	return m_board[line * m_width + column];
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

void Board::SetMasksForFourPlayersGame()
{
	/*QPixmap auxMask;
	for (size_t line = 0; line < kWidth; line++)
	{
		for (size_t column = 0; column < kHeight; column++)
		{
			QString imageLocation = "../TriviadorClient/resource/map4players/";
			imageLocation += QString::number(line) + QString::number(column) + ".png";
			m_board[line * kWidth + column]->setMask((imageLocation).mask());
		}
	}*/
	/*m_board[0].setMask(QPixmap("../TriviadorClient/resource/map4players/00.png").mask());
	m_board[1].setMask(QPixmap("../TriviadorClient/resource/map4players/01.png").mask());
	m_board[2].setMask(QPixmap("../TriviadorClient/resource/map4players/02.png").mask());
	m_board[3].setMask(QPixmap("../TriviadorClient/resource/map4players/03.png").mask());
	m_board[4].setMask(QPixmap("../TriviadorClient/resource/map4players/10.png").mask());
	m_board[5].setMask(QPixmap("../TriviadorClient/resource/map4players/11.png").mask());
	m_board[6].setMask(QPixmap("../TriviadorClient/resource/map4players/12.png").mask());
	m_board[7].setMask(QPixmap("../TriviadorClient/resource/map4players/13.png").mask());
	m_board[8].setMask(QPixmap("../TriviadorClient/resource/map4players/20.png").mask());
	m_board[9].setMask(QPixmap("../TriviadorClient/resource/map4players/21.png").mask());
	m_board[10].setMask(QPixmap("../TriviadorClient/resource/map4players/22.png").mask());
	m_board[11].setMask(QPixmap("../TriviadorClient/resource/map4players/23.png").mask());
	m_board[12].setMask(QPixmap("../TriviadorClient/resource/map4players/30.png").mask());
	m_board[13].setMask(QPixmap("../TriviadorClient/resource/map4players/31.png").mask());
	m_board[14].setMask(QPixmap("../TriviadorClient/resource/map4players/32.png").mask());
	m_board[15].setMask(QPixmap("../TriviadorClient/resource/map4players/33.png").mask());
	m_board[16].setMask(QPixmap("../TriviadorClient/resource/map4players/40.png").mask());
	m_board[17].setMask(QPixmap("../TriviadorClient/resource/map4players/41.png").mask());
	m_board[18].setMask(QPixmap("../TriviadorClient/resource/map4players/42.png").mask());
	m_board[19].setMask(QPixmap("../TriviadorClient/resource/map4players/43.png").mask());
	m_board[20].setMask(QPixmap("../TriviadorClient/resource/map4players/50.png").mask());
	m_board[21].setMask(QPixmap("../TriviadorClient/resource/map4players/51.png").mask());
	m_board[22].setMask(QPixmap("../TriviadorClient/resource/map4players/52.png").mask());
	m_board[23].setMask(QPixmap("../TriviadorClient/resource/map4players/53.png").mask());*/
}

void Board::SetCoordinatesForFourPlayersGame()
{
	m_board[0].setGeometry(25, 25, 25, 25);
	m_board[1].setGeometry(50, 25, 25, 25);
	m_board[2].setGeometry(75, 25, 25, 25);
	m_board[3].setGeometry(100, 25, 25, 25);
	m_board[4].setGeometry(25, 50, 25, 25);
	m_board[5].setGeometry(50, 50, 25, 25);
	m_board[6].setGeometry(75, 50, 25, 25);
	m_board[7].setGeometry(100, 50, 25, 25);
	m_board[8].setGeometry(25, 75, 25, 25);
	m_board[9].setGeometry(50, 75, 25, 25);
	m_board[10].setGeometry(75, 75, 25, 25);
	m_board[11].setGeometry(100, 75, 25, 25);
	m_board[12].setGeometry(25, 100, 25, 25);
	m_board[13].setGeometry(50, 100, 25, 25);
	m_board[14].setGeometry(75, 100, 25, 25);
	m_board[15].setGeometry(100, 100, 25, 25);
	m_board[16].setGeometry(25, 125, 25, 25);
	m_board[17].setGeometry(50, 125, 25, 25);
	m_board[18].setGeometry(75, 125, 25, 25);
	m_board[19].setGeometry(100, 125, 25, 25);
	m_board[20].setGeometry(25, 150, 25, 25);
	m_board[21].setGeometry(50, 150, 25, 25);
	m_board[22].setGeometry(75, 150, 25, 25);
	m_board[23].setGeometry(100, 150, 25, 25);
}

//Territory& Board::operator[](Position pos)
//{
//	const auto& [line, column] = pos;
//
//	if (line >= m_height || column >= m_width) {
//		throw std::out_of_range("Position is out of range!");
//	}
//
//	return m_board[line * m_width + column];
//}

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