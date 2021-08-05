#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Entity.h"
#include "Particle.h"

#define BACKGROUND_MAX_FRAMES 3
#define BACKGROUND_TOTAL 12
#define SHOW_HUNGER_TIME 1000 * 60 * 15
#define MAX_VITAL 100
#define ANIMAL_TEXTURE_SIZE 32

struct AnimalSaveState
{
	int texturesIndex = 0;

	float global_time;
	float interaction_time;
	float animation_time;
	float background_time;
	float night_time;
	float hunger_time;

	float current_animation_speed;

	float waitfor_play;
	float waitfor_eat;
	int waitfor_eat_count = 0;

	float play_key_time;
	bool play_keypress = false;
	int play_count = 0;

	float eat_key_time;
	bool eat_keypress = false;
	int eat_count = 0;

	bool night = false;
	bool showBox = false;
	bool showHunger = false;



	int switch_night_count = 0;
	int background_index = 0;
	int max_background = 0;
	int eat_action = 0;
	int sick_help_count = 0;
	int sick_total_count = 0;

	float hunger = MAX_VITAL;
	int life = MAX_VITAL;

	bool alive = true;

	bool stateChange = true;

	int state;
};

class Animal : public Entity
{
public:
	Animal(std::vector<std::pair<EntityState, std::vector<sf::Texture>>>, int);

	void update(float &) override;
	void draw(sf::RenderWindow &) override;
	int getBackground();
	bool isNight();
	void setIconsPack(std::vector<sf::Texture>);
	void setState(EntityState, float);

	void backupState(AnimalSaveState save);
	AnimalSaveState getBackupState();
private:
	std::vector<sf::Texture> icons;
	std::vector<Particle> particles;
	
	void updateCurrentTextures();
	std::vector<sf::Texture> currentTextures;
	int texturesIndex = 0;
	sf::Sprite currentSprite;

	float global_time;
	float interaction_time;
	float animation_time;
	float background_time;
	float night_time;
	float hunger_time;

	float current_animation_speed;

	float waitfor_play;
	float waitfor_eat;
	int waitfor_eat_count = 0;
	
	float play_key_time;
	bool play_keypress = false;
	int play_count = 0;

	float eat_key_time;
	bool eat_keypress = false;
	int eat_count = 0;

	bool night = false;
	bool showBox = false;
	bool showHunger = false;

	

	int switch_night_count = 0;
	int background_index = 0;
	int max_background = 0;
	int eat_action = 0;
	int sick_help_count = 0;
	int sick_total_count = 0;

	float hunger = MAX_VITAL;
	int life = MAX_VITAL;

	bool alive = true;

	bool isCenter = false;
	bool stateChange = true;
};
