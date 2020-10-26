#include <string>
#include "DoubleBuffering.h"
#include "KeyboardInput.h"
#include "ColorCode.h"
#include "struct.h"
#include "BallMovement.h"

#define WALL "■"
#define PLAYER  "="
#define BALL  "@"
#define DESTROYABLE_WALL "#"

#define DEFAULT_PLAYER_LENGTH 12
#define MAIN_SCREEN_X 200
#define MAIN_SCREEN_Y 200

using namespace std;
//https://tikcode.tistory.com/4

class Screen {
public:
	void Print_Score_Board_Info(DoubleBuffering* dbuff, string str, COORD score_box_xy, short line);
protected:
	void Print_Map_Boundary(DoubleBuffering* dbuff, Box box);
	void Print_Score_Board(DoubleBuffering* dbuff, Score_Box score_box);
};

class Object {
private:
	void Print_Reset_Ball(DoubleBuffering* dbuff, Keyboard key, Ball* ball);
	string repeat_str(string s, int n);
	char* color_set(char* color);
public: 
	void Print_Player(DoubleBuffering* dbuff, Player *player, Keyboard key, Box box);
	void Print_Wall(DoubleBuffering* dbuff, Wall* wall, SWall* swall, Box box);
	void Crash_Wall(Ball* ball, Wall* wall, SWall* swall);
	SWall* Config_Wall(Wall* wall, Box box);
	void Print_Ball(DoubleBuffering* dbuff, Ball *ball, Box box, Player player, Keyboard key);
};

class Main_Screen : public Screen {
public:
	void Print(DoubleBuffering *dbuff, Box box, Score_Box score_box);
};