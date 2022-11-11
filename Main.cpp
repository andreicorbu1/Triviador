#include <iostream>
#include "Board.h"

int main() {
	Board board(5, 3);

	Territory t1("Sebi");
	Territory t2("George");

	board[{0, 0}] = t1;
	board[{1, 2}] = t2;

	std::cout << board;

	return 0;
}