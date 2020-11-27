#pragma once
#include <fstream>
#include <string>
#include "struct.h"
#include "to_string_modified.h"

#define PLAYER_LENGTH_OPTION "player_length="
#define TIME_LIMIT_OPTION "time_limit="
#define BLOCK_LENGTH_OPTION "block_length="
#define PLAYER_NAME_OPTION "player_name="
#define LANGUAGE_OPTION "language="
#define USER_IDENTIFIER "=========="

using namespace std;

class GetFile {
protected:
	ifstream in_conf_file;
	ifstream in_record_file;
	void Close_Record_Stream();
	void Close_Config_Stream();
public:
	GetFile(int player_length, int time_limit, int block_length, string player_name, string language);		//configure file setting
	GetFile();			//record file setting
};

class GetConfig : GetFile{
private:
	int player_length = 12;		//default
	int time_limit = 90;		//default
	int block_length = 5;		//default
	string player_name = DEFAULT_PLAYER_NAME;	//default
	string player_language = "kor";
public:
	GetConfig(Player *player, int *time_limit, Wall *wall);
	int Read_Config_Player_Length();
	int Read_Config_Time_Limit();
	int Read_Config_Block_Length();
	string Read_Config_Player_Name();
};

class GetRecord : GetFile{
private:
	string *infos;
	int record_length=0;
public:
	GetRecord();
	string* Read_Records();
	int Read_Records_Num();
	void Delete_Records();
};

class PutRecord {
public:
	void Put(string username, int detroyed_block, float score, int time_limit, int player_length);
};