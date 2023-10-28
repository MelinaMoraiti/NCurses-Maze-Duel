#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ncurses.h>
#include "MovingCharacter.h"
#include "Engine.h"
int main(int argc, char *argv[])
{
	srand(time(NULL));
    if (argc!=2)
	{
		printf("Usage: %s <Path for map file>\n",argv[0]);
		exit(1);
	}	
	initscr();
	if(has_colors() == FALSE)
	{	
		addstr("Your terminal does not support color\n");
    }
	start_color();
	Engine* gameEngine = new Engine(argv[1],8);
	try
	{	
		gameEngine->LoadMap();
	}
	catch(int e)
	{
		if (e == 1)
		{
			cout<<"Error: Map input file can't be loaded\n";
		}
	}
    gameEngine->startGame();
    refresh();
    delete gameEngine;
	endwin();
	return 0;
}
