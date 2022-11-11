#include <iostream>
#include "Board.h"

int main() {
	Board board(5, 3);

	Territory t;

	board[{1, 2}] = t;

	std::cout << board;

	return 0;
}