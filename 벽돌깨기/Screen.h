#include <string>
#include "DoubleBuffering.h"
#include "KeyboardInput.h"
#include "ColorCode.h"
#include "struct.h"
#include "BallMovement.h"
#include "Sound.h"
#include "Object.h"

using namespace std;
//https://tikcode.tistory.com/4

string Repeat_Str(string s, int n);
short Color_Set(short color);
string Color_Code_Generator(string object, short color);

class Screen {
private:
	DoubleBuffering* dbuff;
public:
	Screen(DoubleBuffering *dbuff);
	void Print_Time_Limit(COORD score_box_xy, int time);
	void Print_Crashed_Block_Num(COORD score_box_xy, int score);
	void Print_Remain_Block_Num(COORD score_box_xy, SWall* swall, int size);
	void Print_Score_Board_Info(string str, COORD score_box_xy, COORD line_xy);
	void Print_Map_Boundary(Box box);
	void Print_Score_Board(Score_Box score_box);
};

class Main_Screen {
private:
	void Print_Main_Title(DoubleBuffering* dbuff, Keyboard *key, short status);
public:
	void Print_Start_Screen(DoubleBuffering *dbuff, Keyboard *key, short status);
	void Print_GameOver_Screen(DoubleBuffering *dbuff, Keyboard *key);
};