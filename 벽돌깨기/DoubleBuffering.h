#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class DoubleBuffering {
public:
	DoubleBuffering(short window_x, short window_y) {
		COORD size = { window_x, window_y }; //Buffer Size

		SMALL_RECT window_size; //Window Size Struct
		window_size.Left = window_size.Top = 0;
		window_size.Right = window_x - 1;
		window_size.Bottom = window_y - 1;

		system("mode con cols=132 lines=60");

		// Make Buffer
		hBuffer[0] = { CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL) };
		hBuffer[1] = { CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL) };

		SetConsoleScreenBufferSize(hBuffer[0], size); // Console Buffer Size Set
		SetConsoleWindowInfo(hBuffer[0], TRUE, &window_size); //Console Size Set

		SetConsoleScreenBufferSize(hBuffer[1], size); // Console Buffer Size Set
		SetConsoleWindowInfo(hBuffer[1], TRUE, &window_size); //Console Size Set

		//First Excute
		Write_Buffer({ 0, 0 }, "");
		Flip_Buffer();
		CleanUp_Buffer(window_x, window_y);
	}

	void Write_Buffer(COORD CursorPosition, string str) {
		DWORD dw;
		Move_Cursor(CursorPosition);
		WriteFile(hBuffer[screen_index], str.c_str(), str.length(), &dw, NULL); //Write to Buffer, c_str -> c-style string https://irontooth.tistory.com/117
	}

	void Flip_Buffer(short delay = 33) {
		Sleep(delay);
		SetConsoleActiveScreenBuffer(hBuffer[screen_index]);
		screen_index = !screen_index;
	}
	void CleanUp_Buffer(short window_x, short window_y) {
		COORD coord = { 0, 0 };
		DWORD dw;
		FillConsoleOutputCharacter(hBuffer[screen_index], ' ', window_x*window_y, coord, &dw);
	}

	void Disable_Buffer() {
		CloseHandle(hBuffer[0]);
		CloseHandle(hBuffer[1]);
	}

private:
	HANDLE hBuffer[2];
	void Move_Cursor(COORD CursorPosition) {
		SetConsoleCursorPosition(hBuffer[screen_index], CursorPosition);
	}
	bool screen_index;

};
