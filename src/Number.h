/*
 * Numbers.h
 *
 *  Created on: Apr 22, 2016
 *      Author: Wendy
 */
#ifndef NUMBER_H_
#define NUMBER_H_
#include "Tile.h"

class Number :public Tile {
private:
	int m_number;
public:
	Number();
	virtual ~Number();
	void setNumber(int n);
	int getNumber();
};

#endif /* NUMBER_H_ */
