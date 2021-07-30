#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include "../Entity.h"

class Animal : public Entity
{
public:
	Animal(std::vector<std::pair<EntityState, std::vector<sf::Texture>>>, int);
		
	void update(float&) override;
	void draw(sf::RenderWindow&) override;
private:
	float time;
};

