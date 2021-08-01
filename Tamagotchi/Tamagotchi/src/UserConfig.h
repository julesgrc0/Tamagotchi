#pragma once
#include<iostream>

struct ConfigObject {
	int musicVolume = 100;
	bool musicEnable = true;
	float musicPitch = 1.0f;
};

class UserConfig
{
public:
	UserConfig(std::string apppath);
	~UserConfig();

	bool loadConfig();

	ConfigObject user;
private:
	std::string app;
};

