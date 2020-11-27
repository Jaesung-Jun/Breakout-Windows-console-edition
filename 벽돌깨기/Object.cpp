#include "Object.h"


string Object::Repeat_Str(string s, int n) {
	string s1 = s;
	for (int i = 0; i < n; i++) {
		s += s1;
	}
	return s;
}

short Object::Color_Set(short color) {
	if (color > 9) {
		color = 1;
	}
	else {
		color++;
	}
	return color;
}


obj_Player::obj_Player(DoubleBuffering *_dbuff, Player *_player){
	dbuff = _dbuff;
	player = _player;
	player->xy = { ((DEFAULT_BOX_SIZE_X + DEFAULT_BOX_X) * 2) / 2, 50 };
	player->destroyed_block = 0;
	player->length = DEFAULT_PLAYER_LENGTH;
}

void obj_Player::Crash_Player(Box box) {
	if ((player->xy.X + player->length) >= box.size.X * 2 + box.xy.X - 1) {
		player->xy.X -= 2;
	}
	else if ((player->xy.X) <= box.xy.X) {
		player->xy.X += 2;
	}
}

void obj_Player::Print_Player(Keyboard key, Box box) {
	key.Player_X_Input(&(player->xy.X));
	Crash_Player(box);
	dbuff->Write_Buffer({ player->xy.X, player->xy.Y }, Repeat_Str(PLAYER, player->length));
}

void obj_Destroyable_Wall::Print_Wall(Wall* wall, Box box) {
	char* color_wall = DESTROYABLE_WALL;

	for (short i = 0; i < wall->nblocks; i++) {
		//default_color = color_set(default_color);
		if (swall[i].is_crashed == FALSE) {
			dbuff->Write_Buffer({ swall[i].xy.X, swall[i].xy.Y }, Repeat_Str(Color_Code_Generator(DESTROYABLE_WALL, swall[i].color), swall[i].length));
		}
	}

	/////////////////////////////////////////////////////////
	//std::string debug5 = std::to_string(wall->nblocks);
	//dbuff->Write_Buffer({ 150, 34 }, debug5);
	////////////////////////////////////////////////////////
}

void obj_Destroyable_Wall::Crash_Wall(Ball* ball, Wall* wall, Player* player) {
	Sound sound;
	BallMovement ball_move;
	for (short i = 0; i < wall->nblocks; i++) {
		if (swall[i].is_crashed == FALSE) {
			if (ball->xy.X <= (swall[i].xy.X + swall[i].length) && ball->xy.X >= swall[i].xy.X && swall[i].xy.Y <= ball->xy.Y && swall[i].xy.Y >= ball->xy.Y) { //if crashed
				if ((swall[i].xy.X + wall->block_length == swall[i + 1].xy.X) || (swall[i].xy.X - wall->block_length == swall[i - 1].xy.X)) { //Horizontal Collision Resolution
					swall[i].is_crashed = TRUE;
					ball->upbound = TRUE;
					ball_move.vec_direction(ball);
					sound.down_pitch_play(200, 10, 1);
				}
				else if ((swall[i].xy.X + wall->block_length != swall[i + 1].xy.X) || (swall[i].xy.X - wall->block_length != swall[i - 1].xy.X)) { //Vertical Collision Resolution
					swall[i].is_crashed = TRUE;
					ball->upbound = FALSE;
					ball_move.vec_direction(ball);
				}
				player->destroyed_block++;
			}
		}
	}
}

obj_Destroyable_Wall::obj_Destroyable_Wall(DoubleBuffering *_dbuff, Wall* _wall, Box box){
	/*
	wall->nblocks = (((box.size.X * 2) / wall->block_length)) * (wall->height);
	wall->width = (((box.size.X * 2) / wall->block_length));

	char** wall_set = new char*[wall->width];

	for (int i = 0; i < wall->height; i++) {
	wall_set[i] = new char[wall->height];
	}

	wall_set = {};

	SWall* swall = new SWall[wall->nblocks]();
	*/
	/*
	for (short i = 0; i < wall->width; i++) {
	for (short j = 0; i < wall->height; k++) {
	swall[num_blocks].xy = { (box.xy.X - 3) + wall->block_length, i + wall->y };
	swall[num_blocks].length = wall->block_length;
	num_blocks++;
	}
	}*/
	dbuff = _dbuff;
	wall = _wall;
	wall->nblocks = ((box.size.X * 2) / wall->block_length) * (wall->height);
	
	swall = new SWall[wall->nblocks]{};

	int l = 0;
	short color = 0;
	short tmp_block_size;
	for (short i = wall->y; i < wall->height + wall->y; i++) {
		for (short j = box.xy.X + 2; j < ((box.size.X * 2) + (box.xy.X + 2)); j += wall->block_length) {
			if (j + wall->block_length >((box.size.X * 2 - 5) + (box.xy.X + 2))) {
				tmp_block_size = ((box.size.X * 2 - 5) % wall->block_length);
				swall[l].xy = { j, i };
				swall[l].length = tmp_block_size;
				swall[l].color = Color_Set(color);
				color++;
				l++;
			}
			else {
				swall[l].xy = { j, i };						//Buffer OverRun Bug Detected!
				swall[l].length = wall->block_length;
				swall[l].color = Color_Set(color);
				l++;
			}
		}
	}
}

int obj_Destroyable_Wall::Remain_Walls() {
	int remain_blocks = 0;
	for (int i = 0; i < wall->nblocks; i++) {
		if (swall[i].is_crashed == FALSE) {
			remain_blocks++;
		}
	}
	return remain_blocks;
}

void obj_Destroyable_Wall::Delete_Swall() {
	delete swall;
}

obj_Ball::obj_Ball(DoubleBuffering *_dbuff, Ball *_ball){
	dbuff = _dbuff;
	ball = _ball;
}


void obj_Ball::Print_Reset_Ball(Keyboard key, Ball* ball) {
	dbuff->Write_Buffer({ ball->xy.X, ball->xy.Y }, BALL);
	//Ball Direction Default Setting
	ball->direction[0] = TRUE;		
	ball->direction[1] = FALSE;
	ball->direction[2] = FALSE;
	ball->direction[3] = FALSE;
	ball->direction_xy = { -1, -1 };
	key.Player_Ball_Input(ball); //Space키를 입력받으면 ball.fall_down을 FALSE로 바꾸고 기본 세팅까지 완료함.
}

void obj_Ball::Crash_Ball(Ball *ball, Box box, Player* player) {
	
	BallMovement ball_move;

	Sound sound;

	if ((ball->xy.X) >= box.size.X * 2 + box.xy.X - 3) { //오른쪽벽
		ball->xy.X -= ball->speed;
		ball->upbound = FALSE;
		ball_move.vec_direction(ball, TRUE);
	}

	else if (ball->xy.X <= box.xy.X + 1) { //왼쪽벽
		ball->xy.X += ball->speed;
		ball->upbound = FALSE;
		ball_move.vec_direction(ball);
	}

	if (ball->xy.Y <= box.xy.Y + 1) { //위쪽 벽에 부딪치면
		ball->xy.Y += ball->speed;
		ball->upbound = TRUE;
		ball_move.vec_direction(ball);
	}
	/*
	if (ball->xy.Y >= player.xy.Y - 1 && ball->xy.X <= (player.xy.X + player.length) && ball->xy.X >= (player.xy.X)) {
	ball->xy.Y -= ball->speed;
	ball->upbound = TRUE;
	ball_move.vec_direction(ball);
	Beep(523, 50);
	}*/
	if (ball->xy.X <= (player->xy.X + player->length) && ball->xy.X >= (player->xy.X)) {
		if (ball->xy.Y >= player->xy.Y - 1 && !(ball->xy.Y >= player->xy.Y + 1)) {
			ball->xy.Y -= ball->speed;
			ball->upbound = TRUE;
			ball_move.vec_direction(ball);
			sound.up_pitch_play(50, 50, 1);
		}
	}
	if ((ball->xy.Y) >= box.size.Y + box.xy.Y) { //아래쪽 벽에 
		//player->destroyed_block--;
		if (player->destroyed_block < 0)
			player->destroyed_block = 0;
		ball->xy.Y -= ball->speed;
		ball->fall_down = TRUE;
		//ptr_direction = ball_move.vec_direction(ball->direction, ball->upbound, FALSE);
		//ball_move.find_direction(ball, ptr_direction);
	}

}

void obj_Ball::Print_Ball(Ball *ball, Box box, Player* player, Keyboard key) {

	if (ball->fall_down) {
		ball->xy = { (player->xy.X + (player->length / 2)), player->xy.Y - 1 };
		Print_Reset_Ball(key, ball);
	}
	else if (!ball->fall_down) {
		
		Crash_Ball(ball, box, player);

		ball->xy.X = (ball->xy.X + (ball->direction_xy.X * ball->speed));
		ball->xy.Y = (ball->xy.Y + (ball->direction_xy.Y * ball->speed));


		//////////////////////////////////////////////////////////////////////////
		/*std::string debug1 = std::to_string(ball->xy.X) + ", " + std::to_string(ball->xy.Y);
		std::string debug2 = std::to_string(ball->direction[0]) + std::to_string(ball->direction[1]) + "," + std::to_string(ball->direction[2]) + std::to_string(ball->direction[3]);
		std::string debug3 = std::to_string(ball->direction_xy.X) + std::to_string(ball->direction_xy.Y);
		std::string debug4 = std::to_string(ball->upbound);
		dbuff->Write_Buffer({ 150, 30 }, debug1);
		dbuff->Write_Buffer({ 150, 31 }, debug2);
		dbuff->Write_Buffer({ 150, 32 }, debug3);
		dbuff->Write_Buffer({ 150, 33 }, debug4);*/
		/////////////////////////////////////////////////////////////////////////

		dbuff->Write_Buffer({ ball->xy.X, ball->xy.Y }, BALL);
	}


}