#ifndef Malfoy_h
#define Malfoy_h
#include "MovingCharacter.h"
#include "Engine.h"
class Malfoy: public MovingCharacter
{
private:
	int score;
public:
	void getMove(int);
	void setScore(const int);
	int getScore()const;
	Malfoy(vector <string> ,pair <unsigned short,unsigned short> loc,short colorNum,int sc=0,char s='M',short bg=COLOR_BLACK,short fg=10);
};

#endif
