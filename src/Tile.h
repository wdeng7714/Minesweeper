/*
 * Tile.h
 *
 *  Created on: Apr 22, 2016
 *      Author: Wendy
 */
#include <string>
#ifndef TILE_H_
#define TILE_H_
using namespace std;
class Tile {
protected:
	char m_display;
	bool m_covered;
	bool m_flagged;
public:
	Tile();
	virtual ~Tile();
	void setDisplay(char display);
	void setCovered(bool covered);
	bool getCovered();
	void flag();
	bool getFlagged();
	char getDisplay();
};

#endif /* TILE_H_ */
