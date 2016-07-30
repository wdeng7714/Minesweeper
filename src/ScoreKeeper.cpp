#include "ScoreKeeper.h"
#include <string>
#include <stdlib.h>
ScoreKeeper::ScoreKeeper(char difficulty) {
	m_difficulty = difficulty;
	switch (m_difficulty) {
	case 'd':
		file = "Debugging.txt";
		break;
	case 'e':
		file = "Easy.txt";
		break;
	case 'm':
		file = "Medium.txt";
		break;
	case 'h':
		file = "Hard.txt";
		break;
	}
	m_scores = new int[1];
	delete m_scores;
	m_entries = 0;
}

ScoreKeeper::~ScoreKeeper() {
	// TODO Auto-generated destructor stub
}
void ScoreKeeper::readScores(string file) {
	m_entries = 0;
	string line;
	readFile.open(file.c_str());
	while (getline(readFile, line)) {
		m_entries++;
	}
	readFile.close();
	readFile.open(file.c_str());
	m_scores = new int[m_entries];
	for (int x = 0; x < m_entries; x++) {
		getline(readFile, line);

		m_scores[x] = atoi(line.c_str());
	}
}
void ScoreKeeper::updateScore(int points) {
	writeFile.open(file.c_str(), ios::app);
	writeFile << points << "\n";
	writeFile.flush();
	writeFile.close();
}
void ScoreKeeper::printScores() {
	switch (m_difficulty) {
	case 'd':
		cout << "_________________________________________________________"
				<< endl;
		cout << "\t SCOREBOARD FOR THE DEBUGGING DIFFICULTY" << endl;
		printTable();
		cout
				<< "Wow look at those amazing scores\nNow try actually playing a real game...\n"
				<< endl;
		break;
	case 'e':
		cout << "_________________________________________________________"
				<< endl;
		cout << "\t SCOREBOARD FOR THE EASY DIFFICULTY" << endl;
		printTable();
		break;
	case 'm':
		cout << "_________________________________________________________"
				<< endl;
		cout << "\t SCOREBOARD FOR THE MEDIUM DIFFICULTY" << endl;
		printTable();
		break;
	case 'h':
		cout << "_________________________________________________________"
				<< endl;
		cout << "\t SCOREBOARD FOR THE HARD DIFFICULTY" << endl;
		printTable();
		break;

	}
}
void ScoreKeeper::printTable() {
	cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
	cout << "\t Place \t\t\t Time Taken" << endl;
	for (int x = 0; x < m_entries; x++) {
		cout << "\t   " << x + 1 << "\t\t\t   " << m_scores[x] << ""
				<< endl;
	}
	cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n\n" << endl;
}
void ScoreKeeper::sortScores() {
	readScores(file.c_str());
	int current;
	for (int x = 1; x < m_entries; x++) {
		current = x;
		while (current > 0 && m_scores[current] < m_scores[current - 1]) {
			int temp = m_scores[current - 1];
			m_scores[current - 1] = m_scores[current];
			m_scores[current] = temp;
			current--;
		}
	}
}
