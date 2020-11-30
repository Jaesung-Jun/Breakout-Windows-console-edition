#include "Sound.h"

void Sound::up_pitch_play(short pitch, short playtime, short repeat) {
	for (short i = 0; i < repeat; i++) {
		Beep(500 + pitch, playtime);
		pitch += pitch;
	}
}
void Sound::down_pitch_play(short pitch, short playtime, short repeat) {
	for (short i = 0; i < repeat; i++) {
		Beep(500 - pitch, playtime);
		pitch -= pitch;
	}
}