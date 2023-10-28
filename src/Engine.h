#ifndef Engine_h
#define Engine_h
#include <fstream>
#include <vector>
#include <string>
#include <ncurses.h>
#include "MovingCharacter.h"
#include "Stone.h"
using namespace std;

enum colorPairs {
    WALL=1,STONE,POTTER,MALFOY,PASSAGE,MENU
};
class Engine
{
private:
	vector <string> Map;
	vector <Stone*> Gemstones;
	vector <MovingCharacter*> Characters;
	string filePath;
public:
	Engine(string,short wallColor=COLOR_WHITE,short passageColor = COLOR_BLACK,short menuColor=14);
	~Engine();
	vector<string> getMap()const;
	void LoadMap();
	void DrawMenu();
	unsigned short GetRandom (int L1, int L2);
    pair<unsigned short,unsigned short> GetRandomLocation();
	pair<unsigned short,unsigned short> GetEmptyRandomLocation();
	void AddStone();
	void addMalfoy();
	void addPotter();
	void insertSymbol(pair<unsigned int,unsigned int> ,char );
	bool isSymbol(pair<unsigned short,unsigned short>,char );
	void startGame();
	void DrawMap(WINDOW* win = stdscr);
	bool isEmpty(pair<unsigned short,unsigned short> location);
};

#endif
