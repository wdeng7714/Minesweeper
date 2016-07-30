/*
 * Game.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: Wendy
 */
#include <iostream>
#include "Game.h"

using namespace std;
Game::Game() {
	m_action = 'o';
	m_row = 0;
	m_column = 0;
	m_difficulty = 'e';
	m_boardType = 'd';
	m_board = new Board;
	delete m_board;
	time(&m_start);
	time(&m_end);
	m_timeTaken = 0;
}

Game::~Game() {
}
void Game::initiate() {
	cout << "Welcome to Minesweeper" << endl;
	cout
			<< "__________________________________________________________\n \t\t\tLEGEND \n__________________________________________________________"
			<< endl;
	cout << "\t o \t\t denotes an UNOPENED TILE" << endl;
	cout << "\t # \t\t denotes a FLAGGED TILE" << endl;
	cout << "\t @ \t\t denotes an OPENED MINE" << endl;
	cout << "   [1,2,3,4,5,6,7,8]\t denote number of adjacent mines\n" << endl;
	cout<<"Pro time saving tip:\nTrying to open an already-opened tile will uncover all the \nsurrounding tiles, given that it's condition has been filled\n"<<endl;
	cout << "PRESS ENTER TO BEGIN..." << endl;
	cin.get();
	createBoard();
}
void Game::createBoard() {
try{
	cout << "Custom board or default board? [c/d]";
	cin >> m_boardType;
	switch (m_boardType) {
	case 'c':
		customBoard();
		m_board->print();
		playerAction();
		break;
	case 'd':
		defaultBoard();
		m_board->print();
		playerAction();
		break;
	default:
		cout << "Invalid board type" << endl;
		//recursively calls the method until a valid board type is inputted
		createBoard();
	}
}catch(ifstream::failure &e){
	cout<<"Invalid input"<<endl;
}

}
void Game::customBoard() {
	int cRows, cColumns, cMines = 0;
	do {
		cout << "Enter the number of rows: ";
		cin >> cRows;
		cout << "Enter the number of columns: ";
		cin >> cColumns;
		if (cRows * cColumns <= 1) {
			cout << "Those dimensions are too small, try again\n\n";
		}
	} while (cRows * cColumns <= 1);
	do {
		cout << "Enter the number of mines: ";
		cin >> cMines;
		if (cMines >= cRows * cColumns) {
			cout
					<< "Too many mines for the dimensions requested, try again\n\n";
		}
	} while (cMines >= cRows * cColumns);

	m_board = new Board(cRows, cColumns, cMines);
	cout << "\nInitiating game with custom settings" << endl;
	time(&m_start);
}
void Game::defaultBoard() {

	cout << "Select a difficulty: [d/e/m/h]";
	cin >> m_difficulty;
	switch (m_difficulty) {
	case 'd':
		cout<< "\n****WARNING****"<<endl;
		cout<<"\nThis setting is for debugging purposes only, since playing a full game apparently takes too long"<<endl;
		cout<<"A 1x2 board with 1 mine will be created for ease of testing the scorekeeper, which doesn't run on custom settings"<<endl;
		cout<<"Since you're obviously playing to have fun and not to find all the bugs and imperfections in my program, pick\nanother difficulty for a real game:)"<<endl;
		m_board = new Board(2, 1, 1);
		cout << "\nInitiating game on DEBUGGING difficulty" << endl << endl;
		break;
	case 'e':
		m_board = new Board(9, 9, 9);
		cout << "\nInitiating game on EASY difficulty" << endl << endl;
		break;
	case 'm':
		m_board = new Board(16, 16, 40);
		cout << "\nInitiating game on MEDIUM difficulty" << endl << endl;
		break;
	case 'h':
		m_board = new Board(16, 30, 99);
		cout << "\nInitiating game on HARD difficulty" << endl << endl;
		break;
	default:
		cout << "Invalid difficulty" << endl;
		//recursively calls the method until a valid difficulty is inputted
		defaultBoard();
	}

	time(&m_start);

}
void Game::playerAction() {
	if (!m_board->getGameOver()) {
		cout << "Coordinate [x y]: ";

		cin >> m_column;
		cin >> m_row;
		while (m_column >= m_board->getColumns() || m_row >= m_board->getRows()) {
			cout << "Invalid coordinates, try again\n\n";
			cout << "Coordinate [x y]: ";
			cin >> m_column;
			cin >> m_row;
		}
		cout << "Action [o/f]: ";
		cin >> m_action;
		processAction();
		cout << "\n\n";
		m_board->print();
		playerAction();
	} else {
		time(&m_end);
		m_timeTaken = difftime(m_end, m_start);
//		if (m_board->getWin()) {
//			winGame();
//		}
		if (m_board->getWin() && m_boardType == 'd') {

			winGame();
		} else if (m_board->getWin() && m_boardType == 'c') {
			cout << "\n\n";
			cout << "*********************************************************"
					<< endl;
			cout << "*\t\tCONGRATULATIONS YOU WIN!!\t\t*" << endl;
			cout << "*********************************************************"
					<< endl;
			cout << "\n\nYour time was: " << m_timeTaken << " seconds" << endl;
			cout
					<< "Scores can only be submitted when playing on default settings"
					<< endl;
		} else {
			cout << "\n\nYOU OPENED A BOMB TILE..." << endl;
			cout << "Your time was: " << m_timeTaken << " seconds" << endl;
			cout << "But you don't get to submit a score because you lost"
					<< endl;
		}
		cout << "\nThank you for playing!";
	}

}
void Game::processAction() {

	switch (m_action) {
	case 'f':
		m_board->flag(m_row, m_column);
		break;
	case 'o':
		m_board->open(m_row, m_column);
		break;
	default:
		cout << endl << "Invalid action \n" << endl;
	}
}
void Game::winGame() {
	char submit;
	cout << "\n\n";
	cout << "*********************************************************" << endl;
	cout << "*\t\tCONGRATULATIONS YOU WIN!!\t\t*" << endl;
	cout << "*********************************************************" << endl;
	cout << "Your time was: " << m_timeTaken << " seconds" << endl;

	ScoreKeeper *sk;
	do {
		cout << "Would you like to submit your score? [y/n]: ";
		cin >> submit;
		switch (submit) {
		case 'y':
			cout << "Submitting score..." << endl;

			sk = new ScoreKeeper(m_difficulty);
			sk->updateScore(m_timeTaken);
			sk->sortScores();
			sk->printScores();
			break;
		case 'n':
			cout << "Your score will not be recorded" << endl;
			break;
		default:
			cout << "Invalid input, try again" << endl;
		}
	} while (submit != 'y' && submit != 'n');

}
