// tictactoe_cli.cpp : Defines the entry point for the application.
//

#include "tictactoe_cli.hpp"

#include <cerrno>
#include <iostream>
#include <span>

void Board::draw() {

	// Use ANSI escape codes to clear the terminal.
	std::cout << "\033[J\033[H";
	std::cout << board << "\n\n";
}

Player& Board::getPlayer(uint32_t num) { return players.at(num); }

bool Board::checkValidMove(uint32_t x, uint32_t y, uint32_t play) {
	bool valid = false;

	//Is that location empty?
	if (board[convertCoord(x, y)] == ' ') {
		board[convertCoord(x, y)] = players.at(play).character;
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
	for (auto x = 0u; x < 3u; ++x) {
		for (auto y = 0u; y < 3u; ++y) {
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
		checker = ' ';
		count = 0;
	}

	/*
		Check horizontally.
	*/
	for (auto y = 0u; y < 3u; ++y) {
		for (auto x = 0u; x < 3u; ++x) {
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
		checker = ' ';
		count = 0;
	}

	/*
		Check diagnolly.
	*/
	return (board[convertCoord(0, 0)] != ' ' && board[convertCoord(0, 0)] == board[convertCoord(1, 1)] && board[convertCoord(0, 0)] == board[convertCoord(2, 2)]) ||
		(board[convertCoord(2, 0)] != ' ' && board[convertCoord(2, 0)] == board[convertCoord(1, 1)] && board[convertCoord(2, 0)] == board[convertCoord(0, 2)]);
}

uint32_t Board::convertCoord(uint32_t x, uint32_t y) const {
	//Convert the given input coordinates to coordinates in the grid.
	uint32_t nx = 2u + (2u * x);
	uint32_t ny = 1u + (2u * y);

	return (ny * boardWidth) + nx;
}

void runGame(int argc, const char** argv)
{
	Board board;
	auto playerTurn = 1u;
	bool gameOver = false;
	std::string errorMsg;

	if(argc > 1)
	{
		std::string_view str{};
		auto args = std::span<const char*>{argv, static_cast<size_t>(argc)};

		for(const std::string_view arg : args)
		{
			if(str.empty() && (arg == "--player1" || arg == "--player2"))
			{
				str = arg;
				continue;
			}

			if(str == "--player1")
			{
				board.getPlayer(0u).name = arg;
			}
			else if (str == "--player2")
			{
				board.getPlayer(1).name = arg;
			}

			str = std::string_view{};
		}
	}

	while (!gameOver) {
		std::string ix, iy;
		int cx{}, cy{};

		if (errorMsg.empty()) {
			playerTurn++;
			if (playerTurn > 1u) { playerTurn = 0u; }
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

		constexpr auto base10 = 10;

		try {
			cx = std::strtol(ix.c_str(), nullptr, base10);
			cy = std::strtol(iy.c_str(), nullptr, base10);

			if(errno == ERANGE) { throw std::exception{}; }
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

		if (!board.checkValidMove(static_cast<uint32_t>(cx), static_cast<uint32_t>(cy), playerTurn)) {
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
