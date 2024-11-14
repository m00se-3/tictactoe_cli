#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>
#include <cstdint>
#include <array>
#include <span>

struct Player {
	std::string name;
	char character;
};

class Board {

public:
	void draw() const;
	[[nodiscard]] bool checkGameResult(char play) const;
	void parseArguments(std::span<const char*> args);
	[[nodiscard]] static bool checkArgument(std::string_view arg);

	constexpr void makeMove(uint32_t x, uint32_t y, char play) { board[convertCoord(x, y)] = play; }
	[[nodiscard]] constexpr Player& getPlayer(uint32_t num) { return players.at(num); }
	[[nodiscard]] constexpr bool checkValidMove(uint32_t x, uint32_t y) const { return board[convertCoord(x, y)] == ' '; }
	
	/**
	 * @brief Transform the world coordinates supplied to the function into an index into the board string.
	 * 
	 *	The formulas for converting are crafted for the exact string the program uses and will yield one of the 9 spots on the game grid.
	 *
	 * @param x 
	 * @param y 
	 * @return constexpr uint32_t 
	 */
	[[nodiscard]] constexpr uint32_t convertCoord(uint32_t x, uint32_t y) const {
		const uint32_t nx = 2u + (2u * x);
		const uint32_t ny = 1u + (2u * y);

		return (ny * boardWidth) + nx;
	}

private:
	std::uint32_t boardWidth = std::string_view{"(  0 1 2 "}.size();
	std::string board = 
R"(  0 1 2 
0  | |  
 -------
1  | |  
 -------
2  | |  )";

	std::array<Player, 2uz> players =  {
		Player{ .name="Player 1", .character='x' },
		Player{ .name="Player 2", .character='o' }
	};
};

void runGame(int argc, const char** argv);


#endif // !TICTACTOE_H
