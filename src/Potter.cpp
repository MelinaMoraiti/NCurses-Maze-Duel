#include <ncurses.h>
#include "Stone.h"
#include "Engine.h"
#include "Potter.h"
#include "MovingCharacter.h"

void Potter::getMove(int KEY)
{
	switch (KEY)
	{
	case 'W' | 'w':  
		if(Map[location.first-1][location.second]!='*') location.first--;
	break; 
	case 'S'| 's': 
		if (Map[location.first+1][location.second]!='*') location.first++;
	break; 
	case 'A' | 'a': 
		if (Map[location.first][location.second-1]!='*') location.second--;
	break; 
 	case 'D' | 'd':  
 		if (Map[location.first][location.second+1]!='*') location.second++;
	break;
	case ' ':
	    if(Map[location.first-1][location.second]!='*') location.first--;
    break;
    default:
    break;
    }
}
int Potter::getScore()const
{
	return score;
}
void Potter::setScore(const int sc)
{
	score = sc;
}
Potter::Potter(vector <string> M,pair <unsigned short,unsigned short> loc,short colorNum,int sc,char s,short bg,short fg) : MovingCharacter(M,loc,colorNum,s,bg,fg)
{
	score =sc;
}