#pragma once
#include<SFML/Graphics.hpp>

enum WindowState {
	INIT,
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
	bool fontload = false;
	int load_size;
	int load_index;

	void update(float&);
	void draw(sf::RenderWindow&);
	
	char* application_path;
	sf::Font font;
	std::vector<sf::Texture> textures;

	sf::Text text(std::string,sf::Vector2f,int,bool diff = false);
};

std::string merge_path(const char* path1, const char* path2);