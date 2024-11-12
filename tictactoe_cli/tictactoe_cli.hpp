#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>
#include <array>

struct Player {
	std::string name;
	char character;
};

class Board {

public:
	void draw();
	Player& getPlayer(uint32_t num);
	bool checkValidMove(uint32_t x, uint32_t y, uint32_t play);
	bool checkGameResult();
	[[nodiscard]] uint32_t convertCoord(uint32_t x, uint32_t y) const;

private:
	uint32_t boardWidth = std::string_view{"(  0 1 2 "}.size();
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
