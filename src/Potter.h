#ifndef Potter_h
#define Potter_h
#include "MovingCharacter.h"
class Potter: public MovingCharacter
{
private:
	int score;
public:
	void getMove(int);
	void setScore(const int);
	int getScore()const;
	Potter(vector <string> M,pair <unsigned short,unsigned short> loc,short colorNum,int sc=0,char s='P',short bg=COLOR_BLACK,short fg=9);
};

#endif
