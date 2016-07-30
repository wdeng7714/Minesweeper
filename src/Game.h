/*
 * Game.h
 *
 *  Created on: Apr 26, 2016
 *      Author: Wendy
 */

#ifndef GAME_H_
#define GAME_H_
#include "Board.h"
#include "ScoreKeeper.h"
#include <time.h>
class Game {
protected:
	Board *m_board;
	char m_action;
	int m_row, m_column;
	char m_difficulty;
	char m_boardType;
	int m_timeTaken;
	time_t m_start;
	time_t m_end;

public:
	Game();
	void initiate();
	void playerAction();
	void processAction();
	void createBoard();
	void customBoard();
	void defaultBoard();
	void winGame();
	virtual ~Game();
};

#endif /* GAME_H_ */
