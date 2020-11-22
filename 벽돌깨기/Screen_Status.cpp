#include "Screen.h"
#include <ctime>
#include "KeyboardInput.h"
using namespace std;

void Main_Screen::Print_Main_Title(Keyboard *key, short status) {
	int color_code1 = 0;
	int color_code2 = 0;
	srand((unsigned int)time(0));
	color_code1 = rand() % 6 + 1;
	srand((unsigned int)time(0) + 30);
	color_code2 = rand() % 6 + 1;

	dbuff->Write_Buffer({ 20, 5 }, Color_Code_Generator("                                   #@@@@  @@@@@@@  @@@@#                                  ", color_code1));
	dbuff->Write_Buffer({ 20, 6 }, Color_Code_Generator("                                   (@@@@  @@@@@@@  @@@@#                                  ", color_code1));
	dbuff->Write_Buffer({ 20, 7 }, Color_Code_Generator("                                   (@@@@  @@@@@@@  @@@@#                                  ", color_code1));
	dbuff->Write_Buffer({ 20, 8 }, Color_Code_Generator("                                   (@@@@  @@@@@@@  @@@@#                                  ", color_code1));
	dbuff->Write_Buffer({ 20, 9 }, Color_Code_Generator("                                   (@@@@  @@@@@@@  @@@@#                                  ", color_code1));
	dbuff->Write_Buffer({ 20, 10 }, Color_Code_Generator("                                   (@@@@  @@@@@@@  @@@@#                                  ", color_code1));
	dbuff->Write_Buffer({ 20, 11 }, Color_Code_Generator("                                   (@@@@  @@@@@@@  @@@@#                                  ", color_code1));
	dbuff->Write_Buffer({ 20, 12 }, Color_Code_Generator("                                   %@@@@  @@@@@@@  @@@@#                                 ", color_code1));
	dbuff->Write_Buffer({ 20, 13 }, Color_Code_Generator("                                   &@@@@  @@@@@@@  @@@@&                                 ", color_code1));
	dbuff->Write_Buffer({ 20, 14 }, Color_Code_Generator("                                   @@@@@  @@@@@@@  @@@@@                                 ", color_code1));
	dbuff->Write_Buffer({ 20, 15 }, Color_Code_Generator("                                  (@@@@@  @@@@@@@  @@@@@#                                ", color_code1));
	dbuff->Write_Buffer({ 20, 16 }, Color_Code_Generator("                                  @@@@@@  @@@@@@@  @@@@@@                                ", color_code1));
	dbuff->Write_Buffer({ 20, 17 }, Color_Code_Generator("                                 @@@@@@/  @@@@@@@  (@@@@@@                               ", color_code1));
	dbuff->Write_Buffer({ 20, 18 }, Color_Code_Generator("                                @@@@@@@   @@@@@@@   @@@@@@@.                             ", color_code1));
	dbuff->Write_Buffer({ 20, 19 }, Color_Code_Generator("                              #@@@@@@@,   @@@@@@@   ,@@@@@@@/                            ", color_code1));
	dbuff->Write_Buffer({ 20, 20 }, Color_Code_Generator("                             @@@@@@@@(    @@@@@@@    (@@@@@@@@                           ", color_code1));
	dbuff->Write_Buffer({ 20, 21 }, Color_Code_Generator("                           @@@@@@@@@*     @@@@@@@     /@@@@@@@@@                         ", color_code1));
	dbuff->Write_Buffer({ 20, 22 }, Color_Code_Generator("                        &@@@@@@@@@@       @@@@@@@       @@@@@@@@@@&                      ", color_code1));
	dbuff->Write_Buffer({ 20, 23 }, Color_Code_Generator("                    .@@@@@@@@@@@@#        @@@@@@@        #@@@@@@@@@@@@.                  ", color_code1));
	dbuff->Write_Buffer({ 20, 24 }, Color_Code_Generator("              .%@@@@@@@@@@@@@@@#          @@@@@@@          #@@@@@@@@@@@@@@@%.            ", color_code1));
	dbuff->Write_Buffer({ 20, 25 }, Color_Code_Generator("             @@@@@@@@@@@@@@@@.            @@@@@@@             @@@@@@@@@@@@@@@@           ", color_code1));
	dbuff->Write_Buffer({ 20, 26 }, Color_Code_Generator("             @@@@@@@@@@@@&                @@@@@@@                &@@@@@@@@@@@@           ", color_code1));
	dbuff->Write_Buffer({ 20, 27 }, Color_Code_Generator("             @@@@@@@#                     @@@@@@@                     #@@@@@@@           ", color_code1));
	dbuff->Write_Buffer({ 20, 28 }, Color_Code_Generator("                                                                                        ", color_code1));
	dbuff->Write_Buffer({ 20, 29 }, Color_Code_Generator("                  @@@@&    @@@@@@@@@@@@@.    @@@@&        @@@@@@@@@/     @@@@@         ", color_code1));
	dbuff->Write_Buffer({ 20, 30 }, Color_Code_Generator("                 @@@@@@@   @@@@@@@@@@@@@.  .@@@@@@@      @@@@@@@@@@@@@   @@@@@         ", color_code1));
	dbuff->Write_Buffer({ 20, 31 }, Color_Code_Generator("                @@@@ @@@@      #@@@@       @@@@ @@@&     @@@@(    @@@@@  @@@@@         ", color_code1));
	dbuff->Write_Buffer({ 20, 32 }, Color_Code_Generator("               @@@@* @@@@(     #@@@@      @@@@* @@@@/    @@@@(  /@@@@@,  @@@@@         ", color_code1));
	dbuff->Write_Buffer({ 20, 33 }, Color_Code_Generator("              %@@@@  .@@@@     #@@@@     &@@@@  .@@@@    @@@@#@@@@@@     @@@@@         ", color_code1));
	dbuff->Write_Buffer({ 20, 33 }, Color_Code_Generator("             ,@@@@@@@@@@@@@    #@@@@    *@@@@@@@@@@@@@   @@@@(.@@@@&     @@@@@         ", color_code1));
	dbuff->Write_Buffer({ 20, 34 }, Color_Code_Generator("             @@@@@@@@@@@@@@@   #@@@@    @@@@@@@@@@@@@@&  @@@@(  @@@@@    @@@@@         ", color_code1));
	dbuff->Write_Buffer({ 20, 35 }, Color_Code_Generator("            @@@@@       @@@@(  #@@@@   @@@@@       @@@@/ @@@@(   %@@@@%  @@@@@         ", color_code1));
	dbuff->Write_Buffer({ 20, 36 }, Color_Code_Generator("           &@@@@        *@@@@  #@@@@  @@@@@        /@@@@ @@@@(    .@@@@@ @@@@@         ", color_code1));

	dbuff->Write_Buffer({ 26, 37 }, Color_Code_Generator(" _______                                 __         ______               __     ", color_code2));
	dbuff->Write_Buffer({ 26, 38 }, Color_Code_Generator("|       \\                               |  \\       /      \\             |  \\    ", color_code2));
	dbuff->Write_Buffer({ 26, 39 }, Color_Code_Generator("| $$$$$$$\\  ______    ______    ______  | $$   __ |  $$$$$$\\ __    __  _| $$_   ", color_code2));
	dbuff->Write_Buffer({ 26, 40 }, Color_Code_Generator("| $$__/ $$ /      \\  /      \\  |      \\ | $$  /  \\| $$  | $$|  \\  |  \\|   $$ \\  ", color_code2));
	dbuff->Write_Buffer({ 26, 41 }, Color_Code_Generator("| $$    $$|  $$$$$$\\|  $$$$$$\\  \\$$$$$$\\| $$_/  $$| $$  | $$| $$  | $$ \\$$$$$$  ", color_code2));
	dbuff->Write_Buffer({ 26, 42 }, Color_Code_Generator("| $$$$$$$\\| $$   \\$$| $$    $$ /      $$| $$   $$ | $$  | $$| $$  | $$  | $$ __ ", color_code2));
	dbuff->Write_Buffer({ 26, 43 }, Color_Code_Generator("| $$__/ $$| $$      | $$$$$$$$|  $$$$$$$| $$$$$$\\ | $$__/ $$| $$__/ $$  | $$|  \\", color_code2));
	dbuff->Write_Buffer({ 26, 44 }, Color_Code_Generator("| $$    $$| $$       \\$$     \\ \\$$    $$| $$  \\$$\\ \\$$    $$ \\$$    $$   \\$$  $$", color_code2));
	dbuff->Write_Buffer({ 26, 45 }, Color_Code_Generator(" \\$$$$$$$  \\$$        \\$$$$$$$  \\$$$$$$$ \\$$   \\$$  \\$$$$$$   \\$$$$$$     \\$$$$ ", color_code2));
	dbuff->Write_Buffer({ 54, 53 }, "Made By Jae-sung Jun");
	dbuff->Write_Buffer({ 45, 57 }, "https://github.com/Jaesung-Jun/Breakout");
	dbuff->Write_Buffer({ 47, 55 }, "2020 2학기 객체지향 프로그래밍 과제");
	dbuff->Write_Buffer({ 30, 50 }, "GAME START");
	dbuff->Write_Buffer({ 60, 50 }, "GAME EXIT");
	dbuff->Write_Buffer({ 90, 50 }, "RECORD VIEW");

	//dbuff->Write_Buffer({ 40, 50 }, std::to_string(status));
	if (status == (int)GAMESTATUS::GAME_START) {
		dbuff->Write_Buffer({ 29, 50 }, ">");
		dbuff->Write_Buffer({ 30, 50 }, Color_Code_Generator("GAME START", 1));
	}
	else if (status == (int)GAMESTATUS::GAME_EXIT) {
		dbuff->Write_Buffer({ 59, 50 }, ">");
		dbuff->Write_Buffer({ 60, 50 }, Color_Code_Generator("GAME EXIT", 1));
	}
	else if (status == (int)GAMESTATUS::RECORD_VIEW) {
		dbuff->Write_Buffer({ 89, 50 }, ">");
		dbuff->Write_Buffer({ 90, 50 }, Color_Code_Generator("RECORD VIEW", 1));
	}
}

void Main_Screen::Print_GameOver_String(Keyboard *key, short status) {
	dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 + 4, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 -2},   ".__ .__..  ..___  .__..  ..___.__ ");
	dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 + 4, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 -1},   "[ __[__]|\\/|[__   |  |\\  /[__ [__)");
	dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 + 4, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2},      "[_./|  ||  |[___  |__| \\/ [___|  \\");

	dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 , GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 + 5 }, "RETRY");
	dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 + 15, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 + 5 }, "SAVE RECORD");
	dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 + 37, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 + 5 }, "EXIT");

	if (status == (int)GAMESTATUS_GAMEOVER::RETRY) {
		dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 - 1, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 + 5 }, ">");
		dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 , GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 + 5 }, Color_Code_Generator("RETRY", 1));
	}
	else if (status == (int)GAMESTATUS_GAMEOVER::SAVE_RECORD) {
		dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 + 14, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 + 5 }, ">");
		dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 + 15, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 + 5 }, Color_Code_Generator("SAVE RECORD", 1));
	}
	else if (status == (int)GAMESTATUS_GAMEOVER::EXIT) {
		dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 + 36, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 + 5 }, ">");
		dbuff->Write_Buffer({ GAME_OVER_X + GAME_OVER_SIZE_X / 2 + 37, GAME_OVER_Y + GAME_OVER_SIZE_Y / 2 + 5 }, Color_Code_Generator("EXIT", 1));
	}
}