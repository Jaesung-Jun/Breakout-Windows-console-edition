#include "GetFile.h"
#include <iostream>


void GetFile::Close_Record_Stream() {
	in_record_file.close();
}
void GetFile::Close_Config_Stream() {
	in_conf_file.close();
}

GetFile::GetFile() {
	in_record_file.open("./game_record.record");
	if (!in_record_file) {
		string record_file_default[3] = {
			"####################################",
			"#	  BreakOut Score Record File",
			"####################################",
		};
		ofstream out_record_file("game_record.record");
		for (int i = 0; i < 3; i++) {
			out_record_file << record_file_default[i] << endl;
		}
		out_record_file.close();
	}
}

GetFile::GetFile(int player_length, int time_limit, int block_length, string player_name, string language) {
	in_conf_file.open("./game_config.conf");
	if (!in_conf_file) {
		string configure_file_info[15] = {
			"############################################################################",
			"# .......................Breakout Configuration File",
			"#",
			"# .........Breakout - 2020 객체지향 프로그래밍 과제",
			"# .......................Made by Jaesung-Jun",
			"#",
			"#",
			"# ...IF YOU MODIFY THIS FILE INCORRECTLY, WILL CAUSE BUGS.",
			"#",
			"# ..player_length : 플레이어(공 발판)의 길이(1 이상의 상수)",
			"# ..time_limit : 제한 시간 (1 이상의 상수)",
			"# ..block_length : 벽돌길이(5-8사이의 값을 추천) (1 이상의 상수)",
			"# ..player_name : 기본 플레이어 이름 (문자열)",
			"# ..Language : 언어설정 (kor, eng, jpn)",
			"###########################################################################",
		};

		string configure_file_default[5] = {
			"player_length=" + to_string(player_length),
			"time_limit=" + to_string(time_limit),
			"block_length=" + to_string(block_length),
			"player_name=" + player_name,
			"language=" + language,
		};
		ofstream out_conf_file("game_config.conf");

		for (int i = 0; i < 15; i++) {
			out_conf_file << configure_file_info[i] << endl;
		}
		for (int i = 0; i < 5; i++) {
			out_conf_file << configure_file_default[i] << endl;
		}
		out_conf_file.close();
	}
}

GetRecord::GetRecord() : GetFile() { 

	string s;
	//file_length = count(istreambuf_iterator<char>(in_record_file), istreambuf_iterator<char>(), '\n');
	while (getline(in_record_file, s)) {
		if (s.front() == '#' || s.front() == '=') {
			continue;
		}
		else {
			record_length++;
		}
	}	
	infos = new string[record_length];
	in_record_file.close();
	in_record_file.open("./game_record.record");
	int i = 0;
	while (getline(in_record_file, s)) {
		if (s.front() == '#' || s.front() == '=') {
			continue;
		}
		else {
			infos[i] = s;
			i++;
		}
	}
	in_record_file.close();
}

string* GetRecord::Read_Records() {
	return infos;
}

int GetRecord::Read_Records_Num() {
	return record_length;
}

void GetRecord::Delete_Records() {
	delete infos;
}


GetConfig::GetConfig(Player *player, int *_time_limit, Wall *wall) : GetFile(player->length, *_time_limit, wall->block_length, player->name, player->language) {
	string s;
	while (getline(in_conf_file, s)) {
		if (s.front() == '#') {
			continue;
		}
		else{
			if (s.find(PLAYER_LENGTH_OPTION) != string::npos) {
				player->length = (short)stoi(s.substr(14));
				player_length = stoi(s.substr(14));
			}
			else if (s.find(TIME_LIMIT_OPTION) != string::npos) {
				*_time_limit = stoi(s.substr(11));
				*_time_limit *= 30;
				time_limit = stoi(s.substr(11));
			}
			else if (s.find(BLOCK_LENGTH_OPTION) != string::npos) {
				wall->block_length = (short)stoi(s.substr(13));
				block_length = stoi(s.substr(13));
			}
			else if (s.find(PLAYER_NAME_OPTION) != string::npos) {
				player->name = s.substr(12);
				player_name = s.substr(12);
			}
			else if (s.find(LANGUAGE_OPTION) != string::npos) {
				player->language = s.substr(9);
				player_language = s.substr(9);
			}
		}
	}
	in_conf_file.close();
}

int GetConfig::Read_Config_Player_Length() {
	return player_length;
}
int GetConfig::Read_Config_Time_Limit() {
	return time_limit;
}
int GetConfig::Read_Config_Block_Length() {
	return block_length;
}
string GetConfig::Read_Config_Player_Name() {
	return player_name;
}

void PutRecord::Put(string username, int detroyed_block, float score, int time_limit, int player_length) {

	ofstream out_record_file("game_record.record", fstream::app);

	string record_list[6] = {
		USER_IDENTIFIER,
		username,
		to_string(detroyed_block),
		to_string_with_precision(score, 0),
		to_string(time_limit),
		to_string(player_length),
	};
	for (int i = 0; i < 6; i++) {
		out_record_file << record_list[i] << endl;
	}
	out_record_file.close();
}
