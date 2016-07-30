/*
 * Board.h
 *
 *  Created on: Apr 22, 2016
 *      Author: Wendy
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include "Bomb.h"
#include "Number.h"

class Board {
private:
	int m_row, m_column, m_numBombs, m_numFlags, m_correctFlags;
	vector<vector<Tile *> > m_board;
	void createBoard();
	int countBomb(int r, int c);
	bool m_gameOver, m_win;
public:
	Board();
	Board(int r, int c, int n);
	void print();
	void flag(int r, int c);
	void open(int r, int c);
	void openAdjacent(int r, int c);
	void fillSpace(int r, int c);
	bool getGameOver();
	bool getWin();
	virtual ~Board();
	void showBombs();
	int getRows();
	int getColumns();
};

#endif /* BOARD_H_ */
