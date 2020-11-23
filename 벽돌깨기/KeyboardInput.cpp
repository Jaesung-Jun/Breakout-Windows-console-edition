#include "KeyboardInput.h"
void Keyboard::Player_X_Input(short *x) {
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		*x -= 2;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		*x += 2;
	}
}

short Keyboard::Game_Status_Choose(short status, int end_num) {
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		Sleep(70);
		if (status <= 0) {
			status = 0;
		}
		else {
			status--;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) < 0) {
		Sleep(70);
		if (status == end_num) {
			status = end_num;
		}
		else {
			status++;
		}
	}
	return status;
}
bool Keyboard::Game_Pause_Check() {
	if (GetAsyncKeyState(VK_ESCAPE) < 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

bool Keyboard::Game_Status_Choose_Check() {
	if (GetAsyncKeyState(VK_RETURN) < 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void Keyboard::Player_Ball_Input(Ball* ball) {
	if (GetAsyncKeyState(VK_SPACE) < 0) {
		ball->fall_down = FALSE;
	}
}

char Keyboard::Input_Alphabet() {
	if (_kbhit()) {
		char key = _getch();
		if (key == 224 || key == 0) {
			key = _getch();
			switch (key) {
			case 75:
			case 77:
				return '\a';
				break;
			}
		}
		else {
			if (40 < key && key < 178)
				return key;
			else if (key == 8) {
				return key;
			}
			else {
				return '\a';
			}
		}
	}
	else {
		return '\a';
	}
	return '\a';
	/*if (GetKeyState(65) < 0)
		return 'A';
	else if (GetKeyState(66) < 0)
		return 'B';
	else if (GetKeyState(67) < 0)
		return 'C';
	else if (GetKeyState(68) < 0)
		return 'D';
	else if (GetKeyState(69) < 0)
		return 'E';
	else if (GetKeyState(70) < 0)
		return 'F';
	else if (GetKeyState(71) < 0)
		return 'G';
	else if (GetKeyState(72) < 0)
		return 'H';
	else if (GetKeyState(73) < 0)
		return 'I';
	else if (GetKeyState(74) < 0)
		return 'J';
	else if (GetKeyState(75) < 0)
		return 'K';
	else if (GetKeyState(76) < 0)
		return 'L';
	else if (GetKeyState(77) < 0)
		return 'M';
	else if (GetKeyState(78) < 0)
		return 'N';
	else if (GetKeyState(79) < 0)
		return 'O';
	else if (GetKeyState(80) < 0)
		return 'P';
	else if (GetKeyState(81) < 0)
		return 'Q';
	else if (GetKeyState(82) < 0)
		return 'R';
	else if (GetKeyState(83) < 0)
		return 'S';
	else if (GetKeyState(84) < 0)
		return 'T';
	else if (GetKeyState(85) < 0)
		return 'U';
	else if (GetKeyState(86) < 0)
		return 'V';
	else if (GetKeyState(87) < 0)
		return 'W';
	else if (GetKeyState(88) < 0)
		return 'X';
	else if (GetKeyState(89) < 0)
		return 'Y';
	else if (GetKeyState(90) < 0)
		return 'Z';
	else if (GetKeyState(VK_SPACE) < 0)
		return ' ';
	else
		return '?';*/
	/*
	for (char i = 65; i < 90; i++) {
		if (GetAsyncKeyState(i) < 0) {
			return to_string(i);
		}

	}*/

}