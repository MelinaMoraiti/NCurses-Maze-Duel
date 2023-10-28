#ifndef Stone_h
#define Stone_h
#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

class Stone 
{
private:
    vector <string> Map;
	pair <unsigned short,unsigned short> location;
    char symbol;
    short backgroundColor;
    short foregroundColor;
	short colorPairNum;
public:
	Stone(vector <string>,pair <unsigned short,unsigned short>,short colorPairNum,char symbol ='S',short backgroundColor = COLOR_BLACK,short foregroundColor = COLOR_YELLOW);
	Stone(Stone& X);
	void teleport(int,int);
	pair<unsigned short,unsigned short> GetRandomLocation();
	pair<unsigned short,unsigned short> GetEmptyRandomLocation();
	short getColorPairNum()const;
	bool isSymbol(pair<unsigned short,unsigned short> ,char );
	pair <unsigned short,unsigned short> getLocation();
	void setRow(unsigned short);
	void setColumn(unsigned short);
	unsigned short getRow()const;
	unsigned short getColumn()const;
    char getSymbol()const;
};

#endif
