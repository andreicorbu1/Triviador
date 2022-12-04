#include "Board.h"


Board::Board(const std::size_t& width, const std::size_t& height)
	: kWidth(width)
	, kHeight(height)
{
}

const std::optional<Territory>& Board::operator[](Position pos) const
{
	const auto& [line, column] = pos;

	if (line >= kHeight || column >= kWidth) {
		throw std::out_of_range("Position is out of range!");
	}

	return m_board[line * kWidth + column];
}


void Board::SetCoordinatesAndSize(uint16_t xPosition, uint16_t yPosition, uint16_t rectangularSize)
{
	uint16_t xPos;
	for (size_t line = 0; line < kHeight; line++)
	{
		xPos = xPosition;
		for (size_t column = 0; column < kWidth; column++)
		{
			m_board[line * kWidth + column]->SetRectangularCoordinates(xPos, yPosition);
			m_board[line * kWidth + column]->SetRectangularSize(rectangularSize, rectangularSize);

			xPos += rectangularSize;
		}
		yPosition += rectangularSize;
	}
}

void Board::PrintBoard(QPaintDevice* device)
{
	QPainter painter(device);
	painter.setPen(QColor(0, 0, 0));
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