#include "Board.h"


Board::Board(const std::size_t& width, const std::size_t& height)
	: kWidth(width)
	, kHeight(height)
{
	SetCoordinates();
}

const std::optional<Territory>& Board::operator[](Position pos) const
{
	const auto& [line, column] = pos;

	if (line >= kHeight || column >= kWidth) {
		throw std::out_of_range("Position is out of range!");
	}

	return m_board[line * kWidth + column];
}


void Board::SetCoordinates()
{
	int xPos = m_xPos;
	int yPos;
	for (int line = 0; line < kHeight; line++)
	{
		yPos = m_yPos;
		for (int column = 0; column < kWidth; column++)
		{
			m_board[line * kHeight + column]->SetRectangularCoordinates(xPos, yPos);
			m_board[line * kHeight + column]->SetRectangularSize(rectangularSize, rectangularSize);

			yPos += rectangularSize;
		}
		xPos += rectangularSize;
	}
}

void Board::PrintBoard(QPaintDevice* device)
{
	QPainter painter(device);
	painter.setPen(QColor(0, 255, 0));
	for (size_t i = 0; i < kSize; i++)
	{
		painter.drawRect(m_board[i]->GetRectangular());
	}
}

std::optional<Territory>& Board::operator[](Position pos)
{
	const auto& [line, column] = pos;

	if (line >= kHeight || column >= kWidth) {
		throw std::out_of_range("Position is out of range!");
	}

	return m_board[line * kWidth + column];
}

std::ostream& operator<<(std::ostream& out, const Board& b)
{
	Board::Position pos;
	auto& [line, column] = pos;
	for (line = 0; line < b.kHeight; line++) {
		for (column = 0; column < b.kWidth; column++) {
			if (b[pos])
				out << *b[pos];
			else
				out << "[____]";
			out << "  ";
		}
		out << "\n\n";
	}

	return out;
}