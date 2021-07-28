#pragma once
#include<SFML/Graphics.hpp>

enum WindowState {
	INIT,
	LOAD_ASSETS,
	START_GAME,
	GAME_RUNNING,
	PAUSE_GAME,
	QUIT
};

class Window
{
public:
	Window();
	~Window();

	bool start();
private:
	WindowState state;

	void init_load();
	void load();

	void update(float&);
	void draw(sf::RenderWindow&);
	
	char* application_path;
	sf::Font font;
	std::vector<sf::Texture> textures;

	void text(std::string,sf::Vector2f,int);
};

std::string join(const char* path1,const char* path2);