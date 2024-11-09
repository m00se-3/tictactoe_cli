// tictactoe_cli.cpp : Defines the entry point for the application.
//

#include "tictactoe_cli.hpp"

#include <iostream>

void Board::draw() {

	// Use ANSI escape codes to clear the terminal.
	std::cout << "\033[J\033[H";
	std::cout << board << "\n\n";
}

Player& Board::getPlayer(int num) { return players[num]; }

bool Board::checkValidMove(int x, int y, int play) {
	bool valid = false;

	//Is that location empty?
	if (board[convertCoord(x, y)] == ' ') {
		board[convertCoord(x, y)] = players[play].character;
		valid = true;
	}
	
	return valid;
}

bool Board::checkGameResult() {
	int count = 0; //Number of consecutive characters found.
	char checker = ' ';

	/*
		Check vertically.
	*/
	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			if (board[convertCoord(x, y)] != ' ') {
				if (checker == ' ') {
					checker = board[convertCoord(x, y)];
					count++;
				}
				else {
					if (board[convertCoord(x, y)] == checker) {
						count++;
					}
					else {
						checker = ' ';
						count = 0;
						break;
					}
				}
			}
			else {
				checker = ' ';
				count = 0;
				break;
			}
		}

		if (count == 3) {
			return true;
		}
		else {
			checker = ' ';
			count = 0;
		}
	}

	/*
		Check horizontally.
	*/
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			if (board[convertCoord(x, y)] != ' ') {
				if (checker == ' ') {
					checker = board[convertCoord(x, y)];
					count++;
				}
				else {
					if (board[convertCoord(x, y)] == checker) {
						count++;
					}
					else {
						checker = ' ';
						count = 0;
						break;
					}
				}
			}
			else {
				checker = ' ';
				count = 0;
				break;
			}
		}

		if (count == 3) {
			return true;
		}
		else {
			checker = ' ';
			count = 0;
		}
	}

	/*
		Check diagnolly.
	*/
	if (
		(board[convertCoord(0, 0)] != ' ' && board[convertCoord(0, 0)] == board[convertCoord(1, 1)] && board[convertCoord(0, 0)] == board[convertCoord(2, 2)]) ||
		(board[convertCoord(2, 0)] != ' ' && board[convertCoord(2, 0)] == board[convertCoord(1, 1)] && board[convertCoord(2, 0)] == board[convertCoord(0, 2)])
		) {
		return true;
	}

	return false;
}

int Board::convertCoord(int x, int y) {
	//Convert the given input coordinates to coordinates in the grid.
	int nx = 2 + 2 * x;
	int ny = 1 + 2 * y;

	return ny * boardWidth + nx;
}

void runGame(int argc, const char** argv)
{
	Board board;
	int playerTurn = -1;
	bool gameOver = false;
	std::string errorMsg;

	if(argc > 1)
	{
		std::string* str = nullptr;

		

		for(int i = 1; i < argc; ++i)
		{
			if(str != nullptr)
			{
				*str = argv[i];
				str = nullptr;
			}

			if(strcmp(argv[i], "--player1") == 0)
			{
				str = &board.getPlayer(0).name;
			}
			else if (strcmp(argv[i], "--player2") == 0)
			{
				str = &board.getPlayer(1).name;
			}
			else
			{
				str = nullptr;
			}
		}
	}

	while (!gameOver) {
		std::string ix, iy;
		int cx, cy;

		if (errorMsg.empty()) {
			playerTurn++;
			if (playerTurn > 1) playerTurn = 0;
		}

		auto& current = board.getPlayer(playerTurn);
		board.draw();

		if (!errorMsg.empty()) {
			std::cout << errorMsg << "\n";
			errorMsg.clear();
		}

		std::cout << current.name << ", select the X coordinate: ";
		std::cin >> ix;

		std::cout << current.name << ", select the Y corrdinate: ";
		std::cin >> iy;

		try {
			cx = std::atoi(ix.c_str());
			cy = std::atoi(iy.c_str());
		}
		catch (const std::exception&) {
			errorMsg = "Invalid input!";
			continue;
		}

		if (cx > 2 || cx < 0) {
			errorMsg = "X coordinate is invalid.";
			continue;
		}

		if (cy > 2 || cy < 0) {
			errorMsg = "Y coordinate is invalid.";
			continue;
		}

		if (!board.checkValidMove(cx, cy, playerTurn)) {
			errorMsg = "The space you selected is already filled.";
			continue;
		}

		gameOver = board.checkGameResult();
	}

	board.draw();

	std::cout << board.getPlayer(playerTurn).name << " wins!\n";
}

int main(int argc, const char** argv)
{
	runGame(argc, argv);
	
	return 0;
}
