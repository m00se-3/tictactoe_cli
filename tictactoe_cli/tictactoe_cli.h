#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <string>

struct Player {
	std::string name;
	char character;
};

class Board {

	const int boardWidth = 9;
	std::string board = 
R"(  0 1 2 
0  | |  
 -------
1  | |  
 -------
2  | |  )";

	Player players[2] = {
		Player{ "Player 1", 'x' },
		Player{ "Player 2", 'o' }
	};

public:
	Board() = default;
	~Board() = default;

	void draw();
	Player& getPlayer(int num);
	bool checkValidMove(int x, int y, int play);
	bool checkGameResult();
	int convertCoord(int x, int y);

};


#endif // !TICTACTOE_H
