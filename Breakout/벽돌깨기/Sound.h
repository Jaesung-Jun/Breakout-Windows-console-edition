#pragma once
#include <Windows.h>
class Sound {
public:
	void up_pitch_play(short pitch, short playtime, short repeat);
	void down_pitch_play(short pitch,short playtime,  short repeat);
};