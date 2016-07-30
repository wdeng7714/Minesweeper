#ifndef SCOREKEEPER_H_
#define SCOREKEEPER_H_
#include <iostream>
#include <fstream>
using namespace std;

class ScoreKeeper {
	ofstream writeFile;
	ifstream readFile;
	string file;
	char m_difficulty;
	int* m_scores;
	int m_entries;

public:
	ScoreKeeper(char difficulty);
	void updateScore(int points);
	void readScores(string file);
	void printScores();
	void printTable();
	void sortScores();
	virtual ~ScoreKeeper();
};

#endif /* SCOREKEEPER_H_ */
