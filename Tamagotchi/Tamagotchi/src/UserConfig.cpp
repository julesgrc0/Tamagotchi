#include "UserConfig.h"
#include "Log.h"
#include <fstream>

UserConfig::UserConfig(std::string apppath)
{
	this->app = apppath;
}

UserConfig::~UserConfig()
{
}

bool UserConfig::loadConfig()
{
	std::ifstream file(this->app + "assets\\config\\user.json");

	if (!file.good())
	{
		LOG() << "[ERR] Fail to load user config file in " << this->app + "assets\\config\\user.json";
		return false;
	}

	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();

	std::string error;
	std::string content((std::istreambuf_iterator<char>(file)),
						(std::istreambuf_iterator<char>()));

	if (!reader->parse(content.c_str(), content.c_str() + content.size(), &this->root, &error))
	{
		LOG() << "[ERR] Fail to parser user config file " << error;
		return false;
	}
	delete reader;

	LOG() << "[INFO] Load user config file ";
	Json::Value musicConf = this->root["music"];
	if (musicConf)
	{
		if (musicConf["pitch"])
		{
			this->user.musicPitch = musicConf["pitch"].asFloat();
		}

		if (musicConf["volume"])
		{
			this->user.musicVolume = musicConf["volume"].asInt();
		}

		if (musicConf["active"])
		{
			this->user.musicEnable = musicConf["active"].asBool();
		}
	}

	Json::Value window = this->root["window"];
	if (window)
	{

		if (window["VerticalSync"])
		{
			this->user.VerticalSync = window["VerticalSync"].asBool();
		}

		if (window["console"])
		{
			this->user.console = window["console"].asBool();
		}

		if (window["showFPS"])
		{
			this->user.showFPS = window["showFPS"].asBool();
		}

		if (window["alwaysOnTop"])
		{
			this->user.alwaysOnTop = window["alwaysOnTop"].asBool();
		}

		if (window["titlebar"])
		{
			this->user.titlebar = window["titlebar"].asBool();
		}

		if (window["position"])
		{
			this->user.win_pos.x = window["position"]["x"].asInt();
			this->user.win_pos.y = window["position"]["y"].asInt();
		}
	}

	if (this->root["data"])
	{
		this->user.first_save = false;

		sf::Int64 musicOffset = this->root["data"]["musicOffset"].asInt64();

		this->user.animal_state.texturesIndex = this->root["data"]["texturesIndex"].asInt();
		this->user.animal_state.global_time = this->root["data"]["global_time"].asFloat();
		this->user.animal_state.interaction_time = this->root["data"]["interaction_time"].asFloat();
		this->user.animal_state.animation_time = this->root["data"]["animation_time"].asFloat();
		this->user.animal_state.background_time = this->root["data"]["background_time"].asFloat();
		this->user.animal_state.night_time = this->root["data"]["night_time"].asFloat();
		this->user.animal_state.hunger_time = this->root["data"]["hunger_time"].asFloat();
		this->user.animal_state.current_animation_speed = this->root["data"]["current_animation_speed"].asFloat();
		this->user.animal_state.waitfor_play = this->root["data"]["waitfor_play"].asFloat();
		this->user.animal_state.waitfor_eat = this->root["data"]["waitfor_eat"].asFloat();
		this->user.animal_state.waitfor_eat_count = this->root["data"]["waitfor_eat_count"].asFloat();
		this->user.animal_state.play_key_time = this->root["data"]["play_key_time"].asFloat();
		this->user.animal_state.play_keypress = this->root["data"]["play_keypress"].asBool();
		this->user.animal_state.play_count = this->root["data"]["play_count"].asInt();
		this->user.animal_state.eat_key_time = this->root["data"]["eat_key_time"].asFloat();
		this->user.animal_state.eat_keypress = this->root["data"]["eat_keypress"].asBool();
		this->user.animal_state.eat_count = this->root["data"]["eat_count"].asInt();
		this->user.animal_state.night = this->root["data"]["night"].asBool();
		this->user.animal_state.showBox = this->root["data"]["showBox"].asBool();
		this->user.animal_state.showHunger = this->root["data"]["showHunger"].asBool();
		this->user.animal_state.switch_night_count = this->root["data"]["switch_night_count"].asInt();
		this->user.animal_state.background_index = this->root["data"]["background_index"].asInt();
		this->user.animal_state.max_background = this->root["data"]["max_background"].asInt();
		this->user.animal_state.eat_action = this->root["data"]["eat_action"].asInt();
		this->user.animal_state.sick_help_count = this->root["data"]["sick_help_count"].asInt();
		this->user.animal_state.sick_total_count = this->root["data"]["sick_total_count"].asInt();
		this->user.animal_state.hunger = this->root["data"]["hunger"].asFloat();
		this->user.animal_state.life = this->root["data"]["life"].asInt();
		this->user.animal_state.alive = this->root["data"]["alive"].asBool();
		this->user.animal_state.stateChange = this->root["data"]["stateChange"].asBool();
		this->user.animal_state.state = this->root["data"]["state"].asInt();

		this->user.musicOffset = musicOffset;
	}

	return true;
}

void UserConfig::writeConfig(AnimalSaveState state, sf::Time musicOffset)
{
	std::ofstream file(this->app + "assets\\config\\user.json");
	if (file.is_open())
	{

		this->root["data"]["musicOffset"] = musicOffset.asMicroseconds();
		this->root["data"]["texturesIndex"] = state.texturesIndex;

		this->root["data"]["global_time"] = state.global_time;
		this->root["data"]["interaction_time"] = state.interaction_time;
		this->root["data"]["animation_time"] = state.animation_time;
		this->root["data"]["background_time"] = state.background_time;
		this->root["data"]["night_time"] = state.night_time;
		this->root["data"]["hunger_time"] = state.hunger_time;

		this->root["data"]["current_animation_speed"] = state.current_animation_speed;

		this->root["data"]["waitfor_play"] = state.waitfor_play;
		this->root["data"]["waitfor_eat"] = state.waitfor_eat;
		this->root["data"]["waitfor_eat_count"] = state.waitfor_eat_count;

		this->root["data"]["play_key_time"] = state.play_key_time;
		this->root["data"]["play_keypress"] = state.play_keypress;

		this->root["data"]["play_count"] = state.play_count;

		this->root["data"]["eat_key_time"] = state.eat_key_time;
		this->root["data"]["eat_keypress"] = state.eat_keypress;

		this->root["data"]["eat_count"] = state.eat_count;

		this->root["data"]["night"] = state.night;
		this->root["data"]["showBox"] = state.showBox;
		this->root["data"]["showHunger"] = state.showHunger;

		this->root["data"]["switch_night_count"] = state.switch_night_count;

		this->root["data"]["background_index"] = state.background_index;
		this->root["data"]["max_background"] = state.max_background;

		this->root["data"]["eat_action"] = state.eat_action;

		this->root["data"]["sick_help_count"] = state.sick_help_count;
		this->root["data"]["sick_total_count"] = state.sick_total_count;

		this->root["data"]["hunger"] = state.hunger;
		this->root["data"]["life"] = state.life;
		this->root["data"]["alive"] = state.alive;

		this->root["data"]["stateChange"] = state.stateChange;

		this->root["data"]["state"] = state.state;

		Json::StreamWriterBuilder builder;
		std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
		writer->write(this->root, &file);

		file.close();
	}
}