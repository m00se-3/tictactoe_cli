#include <tictactoe_cli.hpp>

#include <string>
#include <cerrno>
#include <iostream>
#include <ranges>

#include <ctll/fixed_string.hpp>
#include <ctre.hpp>

static constexpr auto sanitizerPattern = ctll::fixed_string{ "[\\?{};&<>$%:/~*@()'`^#]" };

#ifdef FUZZING
static constexpr auto maxInputAttempts = 32u;
#endif

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

		if(checkArgument(arg)) {
			std::cout << "Invalid value for option: " << str;
			std::exit(EXIT_FAILURE);
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

bool Board::checkArgument(std::string_view arg) {
	return ctre::search<sanitizerPattern>(arg);
}

void Board::run(std::basic_istream<char>* iStream) {
	auto playerTurn = 0u;
	std::string errorMsg;
	#ifdef FUZZING
	auto attempts = 0u;
	
	while (attempts < maxInputAttempts) {
		++attempts;
	#else
	
	while(true) {
	#endif
		std::string ix, iy;
		long cx{}, cy{};

		const auto& current = getPlayer(playerTurn);
		draw();

		if (!errorMsg.empty()) {
			std::cout << errorMsg << "\n";
			errorMsg.clear();
		}

		std::cout << current.name << ", select the X coordinate: ";
		std::getline(*iStream, ix, '\n');

		if(Board::checkArgument(ix)) {
			errorMsg = "Invalid input.";
			continue;
		}

		std::cout << current.name << ", select the Y corrdinate: ";
		std::getline(*iStream, iy, '\n');

		if(Board::checkArgument(iy)) {
			errorMsg = "Invalid input.";
			continue;
		}

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

		if (!checkValidMove(static_cast<uint32_t>(cx), static_cast<uint32_t>(cy))) {
			errorMsg = "The space you selected is already filled.";
			continue;
		}

		makeMove(static_cast<uint32_t>(cx), static_cast<uint32_t>(cy), current.character);
		
		if(checkGameResult(current.character)) { break; }

		playerTurn++;
		if (playerTurn > 1u) { playerTurn = 0u; }
	}

	draw();

	#ifdef FUZZING
	if(attempts == maxInputAttempts) {
		std::cout << "Maximum attempts reached, this limit is intended for testing purposes.\n";
	} else {
		std::cout << getPlayer(playerTurn).name << " wins!\n";
	}
	#else
	std::cout << getPlayer(playerTurn).name << " wins!\n";
	#endif
}

void runGame(int argc, const char** argv) {
	Board board;

	if(argc > 1) {
		board.parseArguments(std::span<const char*>{ argv, static_cast<size_t>(argc) });
	}

	board.run(&std::cin);
}
