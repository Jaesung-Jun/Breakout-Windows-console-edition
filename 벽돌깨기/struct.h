#pragma once
#include <Windows.h>

#define WALL "бс"
#define PLAYER  "="
#define BALL  "@"
#define DESTROYABLE_WALL "#"

#define GAME_OVER_X 7
#define GAME_OVER_Y 20
#define GAME_OVER_SIZE_X 40
#define GAME_OVER_SIZE_Y 15

#define DEFAULT_PLAYER_LENGTH 12
#define MAIN_SCREEN_X 130
#define MAIN_SCREEN_Y 61


#define DEFAULT_BOX_SIZE_X 45
#define DEFAULT_BOX_SIZE_Y 55

#define DEFAULT_SCORE_BOX_SIZE_X 15
#define DEFAULT_SCORE_BOX_SIZE_Y 15

#define DEFAULT_BOX_X 2
#define DEFAULT_BOX_Y 2

#define DEFAULT_SCORE_BOX_X 100
#define DEFAULT_SCORE_BOX_Y 2

#define DEFAULT_WALL_HEIGHT 10;
#define DEFAULT_WALL_Y 8

#define DEFAULT_BLOCK_LENGTH 5; //Recommended to set between 5 - 8 values.

enum class GAMESTATUS {
	GAME_START = 0,
	GAME_EXIT = 1,
	RECORD_VIEW = 2
};

enum class GAMESTATUS_GAMEOVER {
	RETRY = 0,
	SAVE_RECORD = 1,
	EXIT = 2,
};

typedef struct Ball {
	short speed = 1;
	bool fall_down = TRUE;
	bool upbound = FALSE;
	short direction[4] = { TRUE, FALSE, FALSE, FALSE };
	COORD direction_xy = { -1, -1 };
	COORD xy;

} Ball;

typedef struct Player {
	int score = 0;
	COORD xy = { ((DEFAULT_BOX_SIZE_X+DEFAULT_BOX_X)*2)/2, 50 };
	short length = DEFAULT_PLAYER_LENGTH;
} Player;

typedef struct Box {
	COORD size = { DEFAULT_BOX_SIZE_X, DEFAULT_BOX_SIZE_Y };
	COORD xy = { DEFAULT_BOX_X, DEFAULT_BOX_Y };
} Box;

typedef struct SWall {
	short length;
	COORD xy;
	short color = 1;
	bool is_crashed = FALSE;
} SWall;

typedef struct Wall {
	short width;
	short height = DEFAULT_WALL_HEIGHT;
	short block_length = DEFAULT_BLOCK_LENGTH;
	short nblocks;
	short y = DEFAULT_WALL_Y;
} Wall;

typedef struct Score_Box {
	COORD xy = { DEFAULT_SCORE_BOX_X, DEFAULT_SCORE_BOX_Y };
	COORD size = { DEFAULT_SCORE_BOX_SIZE_X, DEFAULT_SCORE_BOX_SIZE_Y };
} Score_Box;