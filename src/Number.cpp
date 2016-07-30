/*
 * Numbers.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: Wendy
 */

#include "Number.h"

Number::Number() :
		Tile() {
	// TODO Auto-generated constructor stub
	m_number = 0;
}

Number::~Number() {
	// TODO Auto-generated destructor stub
}
void Number::setNumber(int n) {
	m_number = n;
m_display = m_number+48;
}
int Number::getNumber() {
	return m_number;
}
