#include <windows.h> 
#include <stdio.h>

#define WIDTH 120
#define HEIGHT 30

float playerX = 0;
float playerY = 0;

float dx = 0, dy = 0;

int main(void)
{
	HANDLE hStdout, hNewScreenBuffer, hNewScreenBuffer2;
	SMALL_RECT srctWriteRect;
	CHAR_INFO chiBuffer[WIDTH * HEIGHT];
	COORD coordBufSize;
	COORD coordBufCoord;
	BOOL fSuccess;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	coordBufSize.X = WIDTH;
	coordBufSize.Y = HEIGHT;

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	srctWriteRect.Left = srctWriteRect.Top = 0;
	srctWriteRect.Right = WIDTH - 1;
	srctWriteRect.Bottom = HEIGHT - 1;

	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		0,
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);                   // reserved; must be NULL 
	hNewScreenBuffer2 = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		0,
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);                   // reserved; must be NULL 
	if (hNewScreenBuffer2 == INVALID_HANDLE_VALUE ||
		hNewScreenBuffer == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		return 1;
	}

	SetConsoleTitle(L"Plz let me double buffering.");
	SetConsoleScreenBufferSize(hNewScreenBuffer, coordBufSize);
	SetConsoleWindowInfo(hNewScreenBuffer, TRUE, &srctWriteRect);
	SetConsoleScreenBufferSize(hNewScreenBuffer2, coordBufSize);
	SetConsoleWindowInfo(hNewScreenBuffer2, TRUE, &srctWriteRect);

	while (true) {

		// update

		if (GetAsyncKeyState(VK_LEFT) < 0) {
			dx--;
		}

		if (GetAsyncKeyState(VK_RIGHT) < 0) {
			dx++;
		}

		if (GetAsyncKeyState(VK_UP) < 0) {
			dy--;
		}

		if (GetAsyncKeyState(VK_DOWN) < 0) {
			dy++;
		}

		playerX += dx;
		playerY += dy;

		dx *= 0.3f;
		dy *= 0.3f;

		static int i = 0;
		HANDLE curScreenBufferHandle;

		if (i % 2 == 0) {
			curScreenBufferHandle = hNewScreenBuffer;
		}
		else {
			curScreenBufferHandle = hNewScreenBuffer2;
		}

		// clear

		for (int y = 0; y < HEIGHT; ++y)
		{
			for (int x = 0; x < WIDTH; ++x)
			{
				chiBuffer[x + WIDTH * y].Char.UnicodeChar = '.';
				chiBuffer[x + WIDTH * y].Attributes = 126;
			}
		}

		// draw player
		int playerCoord = (int)(playerX)+WIDTH * (int)(playerY);

		if (0 < playerCoord && playerCoord < WIDTH * HEIGHT) {
			chiBuffer[playerCoord].Char.UnicodeChar = 'A';
			chiBuffer[playerCoord].Attributes = FOREGROUND_GREEN;
		}

		// present

		fSuccess = WriteConsoleOutput(
			curScreenBufferHandle, // screen buffer to write to 
			chiBuffer,        // buffer to copy from 
			coordBufSize,     // col-row size of chiBuffer 
			coordBufCoord,    // top left src cell in chiBuffer 
			&srctWriteRect);

		if (!SetConsoleActiveScreenBuffer(curScreenBufferHandle)) {
			printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
			return 1;
		}

		Sleep(1 / 60.0f * 1000.0f);

		i++;
	}

	return 0;
}