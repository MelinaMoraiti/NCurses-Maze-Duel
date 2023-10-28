#include <ncurses.h>
#include "Malfoy.h"
#include "Engine.h"
#include "MovingCharacter.h"

void Malfoy::getMove(int KEY)
{ 
   	switch (KEY)
	{
	case KEY_UP :  
		if(Map[location.first-1][location.second]!='*') location.first--;
	break; 
	case KEY_DOWN : 
		if (Map[location.first+1][location.second]!='*') location.first++;
	break; 
	case KEY_LEFT: 
		if (Map[location.first][location.second-1]!='*') location.second--;
	break; 
 	case KEY_RIGHT:  
 		if (Map[location.first][location.second+1]!='*') location.second++;
	break;
	case ' ':
    break;
    default:
    break;
    }
}
int Malfoy::getScore()const
{
	return score;
}
void Malfoy::setScore(const int sc)
{
	score = sc;
}
Malfoy::Malfoy(vector <string> M,pair <unsigned short,unsigned short> loc,short colorNum,int sc,char s,short bg,short fg) : MovingCharacter(M,loc,colorNum,s,bg,fg)
{
   score = sc;
}

