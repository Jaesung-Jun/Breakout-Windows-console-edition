#pragma once
#include "KeyboardInput.h"
#include "struct.h"
#include "Screen.h"
#include "DoubleBuffering.h"

class Object {
protected:
	string Repeat_Str(string s, int n);
	short Color_Set(short color);
};

class obj_Ball : Object {
private:
	DoubleBuffering *dbuff;
	Ball *ball;
	void Crash_Ball(Ball *ball, Box box, Player* player);
	void Print_Reset_Ball(Keyboard key, Ball* ball);
public:
	obj_Ball(DoubleBuffering *_dbuff, Ball *ball);
	void Print_Ball(Ball *ball, Box box, Player* player, Keyboard key);
};

class obj_Player : Object {
private:
	DoubleBuffering *dbuff;
	Player *player;
	void Crash_Player(Box box);
public:
	obj_Player(DoubleBuffering *_dbuff, Player *player);
	void Print_Player(Keyboard key, Box box);
};

class obj_Destroyable_Wall : Object {
private:
	DoubleBuffering *dbuff;
	SWall* swall;
	Wall* wall;
public:
	obj_Destroyable_Wall(DoubleBuffering *_dbuff, Wall* _wall, Box box);
	void Print_Wall(Wall* wall, Box box);
	void Crash_Wall(Ball* ball, Wall* wall, Player* player);
	int Remain_Walls();
	void Delete_Swall();
};