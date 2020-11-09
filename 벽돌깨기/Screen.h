#include <string>
#include "DoubleBuffering.h"
#include "KeyboardInput.h"
#include "ColorCode.h"
#include "struct.h"
#include "BallMovement.h"
#include "Sound.h"

#define WALL "■"
#define PLAYER  "="
#define BALL  "@"
#define DESTROYABLE_WALL "#"

#define DEFAULT_PLAYER_LENGTH 12
#define MAIN_SCREEN_X 130
#define MAIN_SCREEN_Y 80

using namespace std;
//https://tikcode.tistory.com/4

string Repeat_Str(string s, int n);
short Color_Set(short color);
string Color_Code_Generator(string object, short color);

class Screen {
public:
	void Print_Time_Limit(DoubleBuffering* dbuff, COORD score_box_xy, int time);
	void Print_Crashed_Block_Num(DoubleBuffering* dbuff, COORD score_box_xy, int score);
	void Print_Remain_Block_Num(DoubleBuffering* dbuff, COORD score_box_xy, SWall* swall, int size);
protected:
	void Print_Score_Board_Info(DoubleBuffering* dbuff, string str, COORD score_box_xy, COORD line_xy);
	void Print_Map_Boundary(DoubleBuffering* dbuff, Box box);
	void Print_Score_Board(DoubleBuffering* dbuff, Score_Box score_box);
};

class Object {
private:
	void Print_Reset_Ball(DoubleBuffering* dbuff, Keyboard key, Ball* ball);
public: 
	void Print_Player(DoubleBuffering* dbuff, Player *player, Keyboard key, Box box);
	void Print_Wall(DoubleBuffering* dbuff, Wall* wall, SWall* swall, Box box);
	void Crash_Wall(Ball* ball, Wall* wall, SWall* swall, Player* player);
	SWall* Config_Wall(Wall* wall, Box box);
	void Print_Ball(DoubleBuffering* dbuff, Ball *ball, Box box, Player* player, Keyboard key);
};

class Main_Screen : public Screen {
public:
	void Print_Main_Screen(DoubleBuffering *dbuff, Box box, Score_Box score_box);
	void Print_Start_Screen(DoubleBuffering *dbuff);
	void Print_GameOver_Screen(DoubleBuffering *dbuff);
	void Print_Main_Title(DoubleBuffering *dbuff);
};