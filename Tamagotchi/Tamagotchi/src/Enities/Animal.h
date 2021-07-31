#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Entity.h"

#define BACKGROUND_MAX_FRAMES 3
#define BACKGROUND_TOTAL 12
class Animal : public Entity
{
public:
	Animal(std::vector<std::pair<EntityState, std::vector<sf::Texture>>>, int);

	void update(float &) override;
	void draw(sf::RenderWindow &) override;
	int getBackground();
	bool isNight();

private:
	float global_time;
	float interaction_time;
	float animation_time;
	float background_time;
	float night_time;


	bool night = false;
	bool showBox = false;

	int switch_night_count = 0;
	int background_index = 0;
	int max_background = 0;

	int hunger = 100;
	int life = 100;
	int happy = 100;

	void hud(sf::RenderWindow&);
};
