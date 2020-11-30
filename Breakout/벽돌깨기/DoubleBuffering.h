#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class DoubleBuffering {
public:
	DoubleBuffering(short window_x, short window_y);

	void Write_Buffer(COORD CursorPosition, string str);

	void Flip_Buffer(short delay = 33);

	void CleanUp_Buffer(short window_x, short window_y);

	void Disable_Buffer();

private:
	HANDLE hBuffer[2];
	void Move_Cursor(COORD CursorPosition);
	bool screen_index;
};
