/*
 * Tile.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: Wendy
 */

#include "Tile.h"

Tile::Tile() {
	// TODO Auto-generated constructor stub
	m_display = ' ';
	m_covered = true;
	m_flagged = false;
}

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}
void Tile::setDisplay(char display) {
	m_display = display;
}
void Tile::flag() {
	m_flagged = !m_flagged;
}
char Tile::getDisplay() {
	if (m_flagged) {
		return '#';
	} else if (m_covered) {
		return 'o';
	} else {
		return m_display;
	}
}
void Tile::setCovered(bool covered) {
	m_covered = covered;
}
bool Tile::getFlagged(){
	return m_flagged;
}
bool Tile::getCovered() {
	return m_covered;
}
