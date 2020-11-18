#pragma once
#include "KeyboardInput.h"
#include "struct.h"
#include "Screen.h"
#include "DoubleBuffering.h"

class Object {
private:
public:
};

class obj_Ball : Object {
public:
	void Print_Reset_Ball(DoubleBuffering* dbuff, Keyboard key, Ball* ball);
	void Print_Ball(DoubleBuffering* dbuff, Ball *ball, Box box, Player* player, Keyboard key);
};

class obj_Player : Object {
public:
	void Print_Player(DoubleBuffering* dbuff, Player *player, Keyboard key, Box box);
};

class obj_Destroyable_Wall : Object {
public:
	SWall* Config_Wall(Wall* wall, Box box);
	void Print_Wall(DoubleBuffering* dbuff, Wall* wall, SWall* swall, Box box);
	void Crash_Wall(Ball* ball, Wall* wall, SWall* swall, Player* player);
};