#ifndef MovingCharacter_h
#define MovingCharacter_h
#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

class MovingCharacter 
{
protected:
	vector <string> Map;
	pair <unsigned short,unsigned short> location;
    char symbol;
    short backgroundColor;
    short foregroundColor;
	short colorPairNum;
public:
	MovingCharacter(vector <string> ,pair <unsigned short,unsigned short>,short,char,short,short);
	MovingCharacter(MovingCharacter& X);
	virtual void getMove(int) = 0;
	void setPosX(int);
	void setPosY(int);
	int getPosX()const;
	short getColorPairNum();
	pair <unsigned short,unsigned short>  getLocation()const;
	int getPosY()const;
    char getSymbol()const;
};

#endif
