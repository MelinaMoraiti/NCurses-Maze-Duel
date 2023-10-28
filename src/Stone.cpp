#include "MovingCharacter.h"
#include <vector>
#include <string>
#include "Stone.h"
#include "Engine.h"
using namespace std;
Stone::Stone(vector <string> M,pair <unsigned short,unsigned short> l,short colPairCode,char s,short bg,short fg)
{
	 copy(M.begin(), M.end(), back_inserter(Map));
	location.first = l.first;
	location.second = l.second;
    symbol = s;
	colorPairNum = colPairCode;
    init_pair(colorPairNum,fg,bg);
}
Stone::Stone(Stone& X)
{
	copy(X.Map.begin(), X.Map.end(), back_inserter(Map));
	location.first = X.location.first;
	location.second = X.location.second;
    symbol = X.symbol;
}
unsigned short Stone::getRow()const
{
	return location.first;
}
pair<unsigned short,unsigned short>Stone::GetRandomLocation()
{
	pair<unsigned short,unsigned short> randLoc;
	randLoc.first = (rand()%Map.size());   
    randLoc.second = (rand()%Map[0].size());
	return randLoc;
}
bool Stone::isSymbol(pair<unsigned short,unsigned short> location,char sym)
{
	return (Map[location.first][location.second]==sym);
}
pair<unsigned short,unsigned short> Stone::GetEmptyRandomLocation()
{
	pair<unsigned short,unsigned short> emptyRandLoc;
	do
    {
        emptyRandLoc = GetRandomLocation();
    } while (isSymbol(emptyRandLoc,'.') == false);
	return emptyRandLoc;
}
pair <unsigned short,unsigned short> Stone::getLocation()
{
	return location;
}
void Stone::teleport(int rounds,int frequency)
{
	if(rounds % frequency == 0 )
      location = GetEmptyRandomLocation();
}
short Stone::getColorPairNum()const
{
    return colorPairNum;
}
char Stone::getSymbol()const
{
    return symbol;
}
unsigned short Stone::getColumn()const
{
	return location.second;
}
void Stone::setRow(unsigned short X)
{
	location.second = X;
}

void Stone::setColumn(unsigned short Y)
{
	location.second = Y;
}
