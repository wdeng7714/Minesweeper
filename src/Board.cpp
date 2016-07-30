/*
 * Board.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: Wendy
 */

#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <typeinfo>
using namespace std;

Board::Board() {
	m_row = 9;
	m_column = 9;
	m_numBombs = 9;
	m_gameOver = false;
	m_win = false;
	m_numFlags = 0;
	m_correctFlags = 0;
	createBoard();

}

Board::Board(int r, int c, int n) {
	m_row = r;
	m_column = c;
	m_numBombs = n;
	m_numFlags = 0;
	m_correctFlags = 0;
	createBoard();
}
void Board::createBoard() {
	// randomize
	srand(static_cast<unsigned int>(time(0)));

	// set the size of the vector
	m_board.resize(m_row);
	for (int x = 0; x < m_row; x++) {
		m_board[x].resize(m_column);

	}
	// instantiate each element of the polymorphic Tile class vector as a Number
	for (int x = 0; x < m_row; x++) {
		for (int y = 0; y < m_column; y++) {
			m_board[x][y] = new Number;
		}
	}

	// randomly allocate bomb tiles in the board
	for (int x = 0; x < m_numBombs; x++) {
		bool repeat = true;
		while (repeat) {
			int rndRow, rndColumn;
			rndRow = rand() % m_row;
			rndColumn = rand() % m_column;
			if (dynamic_cast<Bomb*>(m_board[rndRow][rndColumn])) {
			} else {
				m_board[rndRow][rndColumn] = new Bomb;
				repeat = false;
			}
		}
	}

	// set numbers
	for (int x = 0; x < m_row; x++) {
		for (int y = 0; y < m_column; y++) {
			if (dynamic_cast<Number*>(m_board[x][y])) {
				Number* tempNumber = new Number;
				tempNumber->setNumber(countBomb(x, y));
				m_board[x][y] = tempNumber;

			}
		}
	}

	// make tiles
	for (int x = 0; x < m_row; x++) {
		for (int y = 0; y < m_column; y++) {
			if (dynamic_cast<Number*>(m_board[x][y])) {
				Number* tempNumber = dynamic_cast<Number*>(m_board[x][y]);
				if (tempNumber->getNumber() == 0) {
					m_board[x][y] = new Tile;
				}
			}
		}
	}
}

void Board::print() {
	// print x axis labels
	cout << "    ";
	for (int x = 0; x < m_column; x++) {
		if (x < 10) {
			cout << x << " ";
		} else {
			cout << x;
		}
	}
	cout << endl << "    ";

	// print top line
	for (int x = 0; x < m_column; x++) {
		cout << "__";
	}
	cout << endl;

	// print all elements of the board that are uncovered
	for (int x = 0; x < m_row; x++) {
		if (x < 10) {
			cout << x << "  |";
		} else {
			cout << x << " |";
		}
		for (int y = 0; y < m_column; y++) {
			cout << m_board[x][y]->getDisplay() << " ";
		}
		cout << "|" << endl;
	}

	// prints bottom line
	cout << "    ";
	for (int x = 0; x < m_column; x++) {
		cout << "¯¯";
	}
	cout << endl;
}
int Board::countBomb(int r, int c) {
	// counts the number of adjacent bombs
	int counter = 0;
	for (int x = r - 1; x <= r + 1; x++) {
		for (int y = c - 1; y <= c + 1; y++) {
			if (x >= 0 && y >= 0 && x < m_row && y < m_column) {
				if (dynamic_cast<Bomb*>(m_board[x][y])) {
					counter++;
				}
			}
		}
	}
	return counter;
}
void Board::flag(int r, int c) {
	if (m_board[r][c]->getCovered()) {
		m_board[r][c]->flag();

		if (m_board[r][c]->getFlagged()) { //tile has been flagged
			m_numFlags++;
			if (dynamic_cast<Bomb*>(m_board[r][c])) { //tile is a mine
				m_correctFlags++;
			}

		} else { //tile has been unflagged
			m_numFlags--;
			if (dynamic_cast<Bomb*>(m_board[r][c])) { //tile is a mine
				m_correctFlags--;
			}
		}
		if (m_numFlags == m_correctFlags && m_numFlags == m_numBombs) {
			m_win = true;
			m_gameOver = true;
		}
	} else {
		cout << "Cannot flag tile because it has already been opened" << endl;
	}
	//cout << "flags: " << m_numFlags << endl << "correct: " << m_correctFlags
	//<< endl << "numBombs: " << m_numBombs << endl;
}
int Board::getRows() {
	return m_row;
}
int Board::getColumns() {
	return m_column;
}

void Board::open(int r, int c) {
	if (!m_board[r][c]->getFlagged() && m_board[r][c]->getCovered()) {
		m_board[r][c]->setCovered(false);

		if (dynamic_cast<Bomb*>(m_board[r][c])) {
			showBombs(); //if a mine tile is opened, uncover all bombs and call game over
			m_gameOver = true;
		}
		if (!dynamic_cast<Bomb*>(m_board[r][c]) //if a blank tile is opened, uncover all adjacent blank tiles until a number is reached
		&& !dynamic_cast<Number*>(m_board[r][c])) {
			fillSpace(r, c);
		}

	} else if (!m_board[r][c]->getCovered()) {
		openAdjacent(r, c);
	} else {
		cout << "Tile cannot be opened because it has been flagged" << endl;
	}
}
void Board::openAdjacent(int r, int c) {
	int adjFlags = 0; //counts the number of flags surrounding the current tile
	for (int x = r - 1; x <= r + 1; x++) {
		for (int y = c - 1; y <= c + 1; y++) {
			if (x >= 0 && y >= 0 && x < m_row && y < m_column) {
				if (m_board[x][y]->getFlagged()) {
					adjFlags++;
				}
			}
		}
	}
	if (adjFlags == m_board[r][c]->getDisplay() - 48) {
		for (int x = r - 1; x <= r + 1; x++) { //if a blank tile is opened, uncover all adjacent blank tiles until a number is reached
			for (int y = c - 1; y <= c + 1; y++) {
				if (x >= 0 && y >= 0 && x < m_row && y < m_column) {
					if (!m_board[x][y]->getFlagged()) {
						m_board[x][y]->setCovered(false);
						if (!dynamic_cast<Bomb*>(m_board[x][y])
								&& !dynamic_cast<Number*>(m_board[x][y])) {
							fillSpace(x, y);
						}
					}
				}
			}
		}
	} else {
		if (dynamic_cast<Number*>(m_board[r][c])) {
			cout
					<< "You have not satisfied the conditions required to open adjacent tiles"
					<< endl;
		} else {
			cout << "That's already opened..." << endl;
		}
	}
}
void Board::fillSpace(int r, int c) {
	for (int x = r - 1; x <= r + 1; x++) {	//checks tiles surrounding tiles
		for (int y = c - 1; y <= c + 1; y++) {
			if (x >= 0 && y >= 0 && x < m_row && y < m_column) {
				if (!(x == r && y == c)) {
					if (!dynamic_cast<Bomb*>(m_board[x][y])
							&& !dynamic_cast<Number*>(m_board[x][y])) {
						if (m_board[x][y]->getCovered()) {
							m_board[x][y]->setCovered(false);
							fillSpace(x, y);
						}
					} else {
						m_board[x][y]->setCovered(false);
					}
				}
			}
		}
	}
}
void Board::showBombs() {
	for (int x = 0; x < m_row; x++) {
		for (int y = 0; y < m_column; y++) {
			if (dynamic_cast<Bomb*>(m_board[x][y])) {
				m_board[x][y]->setCovered(false);
			}
		}
	}
}
bool Board::getGameOver() {
	return m_gameOver;
}
bool Board::getWin() {
	return m_win;
}

Board::~Board() {
// TODO Auto-generated destructor stub
}

