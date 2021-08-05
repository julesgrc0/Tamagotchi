#pragma once
#include<iostream>
#include <json/json.h>
#include "./Enities/Animal.h"
struct ConfigObject {
	int musicVolume = 100;
	bool musicEnable = true;
	float musicPitch = 1.0f;

	bool console = true;
	bool showFPS = true;
	bool alwaysOnTop = false;
	bool VerticalSync = false;
	bool titlebar = true;
	sf::Vector2i win_pos = sf::Vector2i(-1,-1);

	bool first_save = true;
	AnimalSaveState animal_state;
	sf::Int64 musicOffset;
};

class UserConfig
{
public:
	UserConfig(std::string apppath);
	~UserConfig();

	bool loadConfig();
	void writeConfig(AnimalSaveState state,sf::Time musicOffset);

	ConfigObject user;
private:
	std::string app;
	Json::Value root;
};

