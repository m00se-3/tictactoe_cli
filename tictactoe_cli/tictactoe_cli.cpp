// tictactoe_cli.cpp : Defines the entry point for the application.
//

#include <tictactoe_cli.hpp>

#include <cerrno>
#include <iostream>
#include <ranges>

void Board::draw() const {

	// Use ANSI escape codes to clear the terminal.
	std::cout << "\033[2J\033[H";
	std::cout << board << "\n\n";
}

bool Board::checkGameResult(char play) const {
	int count = 0; //Number of consecutive characters found.

	/*
		Check vertically.
	*/
	for (auto x = 0u; x < 3u; ++x) {
		for (auto y = 0u; y < 3u; ++y) {
			if (board[convertCoord(x, y)] == play) {
				++count;
			}
			else {
				count = 0;
				break;
			}
		}

		if (count == 3) {
			return true;
		}
		count = 0;
	}

	/*
		Check horizontally.
	*/
	for (auto y = 0u; y < 3u; ++y) {
		for (auto x = 0u; x < 3u; ++x) {
			if (board[convertCoord(x, y)] == play) {
				++count;
			}
			else {
				count = 0;
				break;
			}
		}

		if (count == 3) {
			return true;
		}
		count = 0;
	}

	/*
		Check diagnolly.
	*/
	return (board[convertCoord(0, 0)] != ' ' && board[convertCoord(0, 0)] == board[convertCoord(1, 1)] && board[convertCoord(0, 0)] == board[convertCoord(2, 2)]) ||
		(board[convertCoord(2, 0)] != ' ' && board[convertCoord(2, 0)] == board[convertCoord(1, 1)] && board[convertCoord(2, 0)] == board[convertCoord(0, 2)]);
}

void Board::parseArguments(std::span<const char*> args) {
	std::string_view str{};

	for(const std::string_view arg : std::ranges::drop_view{ args, 1u }) {
		if(str.empty() && (arg == "--player1" || arg == "--player2")) {
			str = arg;
			continue;
		}

		if(str == "--player1") {
			players.at(0u).name = arg;
		}
		else if (str == "--player2") {
			players.at(1u).name = arg;
		}

		str = std::string_view{};
	}
}

void runGame(int argc, const char** argv) {
	Board board;
	auto playerTurn = 0u;
	std::string errorMsg;

	if(argc > 1) {
		board.parseArguments(std::span<const char*>{ argv, static_cast<size_t>(argc) });
	}

	while (true) {
		std::string ix, iy;
		int cx{}, cy{};

		const auto& current = board.getPlayer(playerTurn);
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

		cx = std::strtol(ix.c_str(), nullptr, base10);
		cy = std::strtol(iy.c_str(), nullptr, base10);

		if(errno == ERANGE) { 
			errorMsg = "Invalid input.";
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

		if (!board.checkValidMove(static_cast<uint32_t>(cx), static_cast<uint32_t>(cy))) {
			errorMsg = "The space you selected is already filled.";
			continue;
		}

		board.makeMove(static_cast<uint32_t>(cx), static_cast<uint32_t>(cy), current.character);
		
		if(board.checkGameResult(current.character)) { break; }

		playerTurn++;
		if (playerTurn > 1u) { playerTurn = 0u; }
	}

	board.draw();

	std::cout << board.getPlayer(playerTurn).name << " wins!\n";
}
