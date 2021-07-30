#pragma once
#include<SFML/Graphics.hpp>
#include "Entity.h"
#include "./Enities/Animal.h"

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
	
	Animal* animal;


	std::vector<
		std::pair<
		int, // type id
		std::vector< // animation list
				std::pair<
					EntityState, // state
					std::vector<sf::Texture> // state textures
				>
			>
		>
	> entityTextures;

	sf::Text text(std::string,sf::Vector2f,int,bool diff = false);
};

std::string merge_path(const char* path1, const char* path2);