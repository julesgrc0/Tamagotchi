#include "UserConfig.h"
#include "Log.h"
#include<json/json.h>
#include<fstream>

UserConfig::UserConfig(std::string apppath)
{
	this->app = apppath;
}

UserConfig::~UserConfig()
{

}

bool UserConfig::loadConfig()
{
	std::ifstream file(this->app+"assets\\config\\user.json");
	
	if (!file.good())
	{
		LOG() << "[ERR] Fail to load user config file in "<< this->app + "assets\\config\\user.json";
		return false;
	}

	Json::Value root;
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	std::string error;
	std::string content((std::istreambuf_iterator<char>(file)),
		(std::istreambuf_iterator<char>()));

	if (!reader->parse(content.c_str(), content.c_str() + content.size(),&root,&error))
	{
		LOG() << "[ERR] Fail to parser user config file " << error;
		return false;
	}
	delete reader;

	LOG() << "[INFO] Load user config file ";
	Json::Value musicConf = root["music"];
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

	Json::Value window = root["window"];
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
	}

	return true;
}