#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "MovingCharacter.h"
#include <ncurses.h>
#include <new>
#include <cstdlib>
#include "Malfoy.h"
#include "Engine.h"
#include "Potter.h"

using namespace std;

void Engine::LoadMap()
{
	string str;
	ifstream inputStream(filePath);
	if (!inputStream.is_open())
	{
		throw 1;
	}
    while(getline (inputStream,str))
	{
		Map.push_back(str);
	} 
	inputStream.close();
}
Engine::~Engine()
{
	for(Stone* gemstone:Gemstones)
		delete gemstone;
	for(MovingCharacter* Character:Characters)
		delete Character;
}
Engine::Engine(string f,short wallColor,short passageColor,short menuColor)
{
	filePath = f;
    init_pair(colorPairs::WALL,wallColor,wallColor);
    init_pair(colorPairs::PASSAGE,passageColor,passageColor);
	init_pair(colorPairs::MENU,menuColor,COLOR_BLACK);
}

void Engine::DrawMap(WINDOW* win)
{
	for (int i = 0;i < Map.size();i++)
	{
		for (int j = 0;j < Map[0].size();j++)
		{	 
		   if (Map[i][j] == '*')
		   {
		   	  wattron(win,COLOR_PAIR(colorPairs::WALL));   
		   	  mvwaddch(win,i,j,Map[i][j]);
              wattroff(win,COLOR_PAIR(colorPairs::WALL));   
		   }
		   else if(Map[i][j] =='.')
           {
              wattron(win,COLOR_PAIR(colorPairs::PASSAGE));  
              mvwaddch(win,i,j,' ');
              wattroff(win,COLOR_PAIR(colorPairs::PASSAGE)); 
           }
		}
	    mvwaddch(win,i,Map[0].size(),'\n');
    }
    wrefresh(win);
}
unsigned short Engine:: GetRandom (int L1, int L2)
{
    return rand () % (L2 - L1 + 1) + L1;
}
pair<unsigned short,unsigned short> Engine::GetRandomLocation()
{
	pair<unsigned short,unsigned short> randLoc;
	randLoc.first = (rand() % Map.size());   
    randLoc.second = (rand() % Map[0].size());
	return randLoc;
}
pair<unsigned short,unsigned short> Engine::GetEmptyRandomLocation()
{
	pair<unsigned short,unsigned short> emptyRandLoc;
	do
    {
        emptyRandLoc = GetRandomLocation();
    } while (isSymbol(emptyRandLoc,'.') == false);
	return emptyRandLoc;
}

bool Engine::isEmpty(pair<unsigned short,unsigned short> location)
{
	return (Map[location.first][location.second]=='.');
}
vector<string> Engine::getMap()const
{
    return Map;
}
void Engine::addPotter()
{
    pair<unsigned short,unsigned short> randLoc;
    randLoc = GetEmptyRandomLocation();
    Potter*  P = new Potter(Map,randLoc,colorPairs::POTTER);
    Characters.push_back(P);
}
void Engine::addMalfoy()
{
    pair<unsigned short,unsigned short> randLoc;
   randLoc = GetEmptyRandomLocation();
    Malfoy*  Mal = new Malfoy(Map,randLoc,colorPairs::MALFOY);
    Characters.push_back(Mal);
}
void Engine::AddStone()
{
   pair<unsigned short,unsigned short> randLoc;
   randLoc = GetEmptyRandomLocation();
   Stone* S  = new Stone(Map,randLoc,colorPairs::STONE);
   Gemstones.push_back(S);
   Map[randLoc.first][randLoc.second] = S->getSymbol();
}
void Engine::insertSymbol(pair<unsigned int,unsigned int> loc,char symbol)
{
    Map[loc.first][loc.second] = symbol;
}
bool Engine::isSymbol(pair<unsigned short,unsigned short> location,char sym)
{
	return (Map[location.first][location.second]==sym);
}
void Engine::DrawMenu()
{
	keypad(stdscr,TRUE);
	noecho();
	curs_set(0);
	attron(COLOR_PAIR(colorPairs::MENU));
	mvprintw(9,45,"MAIN MENU");
	string choices[3] = {"Play Game","Quit"};
	int choice=1;
	int highlight =0;
	while (choice!='\n')
	{
		for (int i = 0;i < 2;i++)
		{
			if (highlight==i)
			{
				attron(COLOR_PAIR(colorPairs::MENU));
				attron(A_REVERSE);
			}
			mvprintw(11+i,45,"%s",choices[i].c_str());
		    attroff(A_REVERSE);
		}
	    choice = getch();
	    switch(choice)
	    {
		 case KEY_UP:
		 	highlight--;
		 	if (highlight == -1) highlight =0;
		   break;
		 case KEY_DOWN:
			highlight++;
			if (highlight == 2) highlight =1;
			break;
		 default: break;
	    }
	}
	if (highlight == 0)
	{
		clear();
		startGame();
	}	
	else 
	{

	}
    refresh();
}
void Engine::startGame()
{
	curs_set(FALSE);
	int ch;
	int enemyScore,playerScore,rounds;
	enemyScore=playerScore=rounds = 0;
	bool gameEnds = false;
	clear();
	keypad (stdscr,TRUE);
	noecho();
    AddStone();
    addMalfoy();
	addPotter();
    DrawMap();
	attron(COLOR_PAIR(colorPairs::POTTER));
	mvprintw(1,65,"Potter controls their character using WASD keys");
	attroff(COLOR_PAIR(colorPairs::POTTER));
	attron(COLOR_PAIR(colorPairs::MALFOY));
	mvprintw(3,65,"Malfoy controls their character using arrow keys");
	attroff(COLOR_PAIR(colorPairs::MALFOY));
	attron(COLOR_PAIR(colorPairs::MENU));
	mvprintw(5,65,"Press ESC to go to Main Menu");
	attroff(COLOR_PAIR(colorPairs::MENU));
    do
    {
		ch = getch(); 
		rounds++;
		attron(COLOR_PAIR(colorPairs::MENU));
		mvprintw(7,65,"Round: %d",rounds);
		attroff(COLOR_PAIR(colorPairs::MENU));
        for(MovingCharacter* Character : Characters)
        {
			Malfoy* Player = dynamic_cast<Malfoy*> (Character);
			Potter* Enemy = dynamic_cast<Potter*> (Character);
			mvaddch(Character->getPosX(),Character->getPosY(),' ');
			insertSymbol(Character->getLocation(),'.');
			Character->getMove(ch);
			attron(COLOR_PAIR(Character->getColorPairNum()));
	        mvaddch(Character->getPosX(),Character->getPosY(),Character->getSymbol());
			attroff(COLOR_PAIR(Character->getColorPairNum()));
			insertSymbol(Character->getLocation(),Character->getSymbol());
			for(Stone *S : Gemstones) 
			{
				mvaddch(S->getRow(),S->getColumn(),' ');
				insertSymbol(S->getLocation(),'.');
				S->teleport(rounds,GetRandom(10,30));
				attron(COLOR_PAIR(S->getColorPairNum()));
				mvaddch(S->getRow(),S->getColumn(),ACS_DIAMOND);
				attroff(COLOR_PAIR(S->getColorPairNum()));
				insertSymbol(S->getLocation(),S->getSymbol());
				if(isSymbol(Character->getLocation(),S->getSymbol()))
				{
					insertSymbol(Character->getLocation(),Character->getSymbol());
					Gemstones.pop_back();
					if (Player != nullptr) 
					{    Player->setScore(Player->getScore() + 1);
					     enemyScore = Player->getScore();
					}
					if(Enemy != nullptr) 
					{ Enemy->setScore(Enemy->getScore() + 1);
					   playerScore = Enemy->getScore();
					} 
				} 
			} 
        }
		if(Gemstones.size() == 0)
		{
			gameEnds=true;
			clear();
			if(playerScore > enemyScore)
			{
				attron(COLOR_PAIR(colorPairs::POTTER));
				mvaddstr(15,50,"Potter Won!");
				attroff(COLOR_PAIR(colorPairs::POTTER));
			} 
		    else if (enemyScore > playerScore)
			{
				attron(COLOR_PAIR(colorPairs::MALFOY));
				mvaddstr(15,50,"Malfoy Won!");
				attroff(COLOR_PAIR(colorPairs::MALFOY));
			}
			else mvaddstr(15,50,"DRAW !");
			getch();
		}
		if (ch == 27 ) gameEnds = true;	
    } while (gameEnds!=true);
	for(MovingCharacter* Character : Characters) Characters.pop_back();
	for(Stone *S : Gemstones) Gemstones.pop_back();
	clear();
	DrawMenu();
    refresh();	
}
