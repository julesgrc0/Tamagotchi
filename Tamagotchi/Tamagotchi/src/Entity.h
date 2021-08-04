#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>

enum EntityState {
	ANGRY,
	ENERGIE,
	HAPPY,
	LOOP,
	SICK,
	STATIC,
	WAIT
};

class Entity
{
public:
	Entity(std::vector<std::pair<EntityState,std::vector<sf::Texture>>>,int);
	Entity(std::vector<sf::Texture>, int);
	Entity(int);
	~Entity();
	
	EntityState state;
	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Vector2f size = sf::Vector2f(0,0);
	float angle;

	bool aabb(Entity&);
	static EntityState getStatefromString(std::string);
	static std::string getStatetoString(EntityState);
	virtual void update(float&);
	virtual void draw(sf::RenderWindow&);

protected:
	std::vector<std::pair<EntityState, std::vector<sf::Texture>>> textures;
	std::vector<sf::Texture> textures_list;
	int id;
};

