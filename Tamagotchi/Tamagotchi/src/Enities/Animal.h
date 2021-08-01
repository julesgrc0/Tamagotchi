#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Entity.h"

#define BACKGROUND_MAX_FRAMES 3
#define BACKGROUND_TOTAL 12
#define SHOW_HUNGER_TIME 1000 * 60 * 15
#define MAX_VITAL 4

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
	float hunger_time;
	

	bool night = false;
	bool showBox = false;
	bool showHunger = false;

	int switch_night_count = 0;
	int background_index = 0;
	int max_background = 0;
	int eat_action = 0;

	float hunger = MAX_VITAL;
	int life = MAX_VITAL;
	float happy = MAX_VITAL;

	bool alive = true;

	void hud(sf::RenderWindow&);
};
