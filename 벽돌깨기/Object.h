#pragma once
#include "KeyboardInput.h"
#include "struct.h"
#include "Screen.h"
#include "DoubleBuffering.h"

class Object {
protected:
	DoubleBuffering *dbuff;
public:
	Object(DoubleBuffering *_dbuff);
};

class obj_Ball : Object {
private:
	Ball *ball;
	void Crash_Ball(Ball *ball, Box box, Player* player);
	void Print_Reset_Ball(Keyboard key, Ball* ball);
public:
	obj_Ball(Ball *ball, short direction[4], COORD direction_xy, short speed);
	void Print_Ball(Ball *ball, Box box, Player* player, Keyboard key);
};

class obj_Player : Object {
private:
	Player *player;
	void Crash_Player(Box box);
public:
	obj_Player(Player *player);
	void Print_Player(Keyboard key, Box box);
};

class obj_Destroyable_Wall : Object {
private:
	SWall* swall;
	Wall* wall;
public:
	obj_Destroyable_Wall(Wall* _wall, Box box);
	void Print_Wall(Wall* wall, Box box);
	void Crash_Wall(Ball* ball, Wall* wall, Player* player);
	int Remain_Walls();
	void Delete_Swall();
};