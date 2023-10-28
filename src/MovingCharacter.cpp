#include "MovingCharacter.h"
#include <vector>
#include <string>
#include "Engine.h"
using namespace std;
MovingCharacter::MovingCharacter(vector <string> M,pair <unsigned short,unsigned short> loc,short colorNum,char s,short bg,short fg)
{
    copy(M.begin(), M.end(), back_inserter(Map));
	location.first = loc.first;
	location.second = loc.second;
    symbol  =s;
    backgroundColor = bg;
    foregroundColor = fg; 
    colorPairNum = colorNum;
    init_pair(colorNum,fg,bg);
}
MovingCharacter::MovingCharacter(MovingCharacter& X)
{
    copy(X.Map.begin(), X.Map.end(), back_inserter(Map));
	location.first = X.location.first;
	location.second = X.location.second;
    symbol =X.symbol;
    backgroundColor = X.backgroundColor;
    foregroundColor = X.foregroundColor;
    colorPairNum = X.colorPairNum;
}
pair <unsigned short,unsigned short> MovingCharacter::getLocation()const
{
	return location;
}
short MovingCharacter::getColorPairNum()
{
    return colorPairNum;
}
char MovingCharacter::getSymbol()const
{
    return symbol;
}
int MovingCharacter::getPosX()const
{
	return location.first;
}
int MovingCharacter::getPosY()const
{
	return location.second;
}
void MovingCharacter::setPosX(int X)
{
	location.first = X;
}

void MovingCharacter::setPosY(int Y)
{
	location.second = Y;
}
