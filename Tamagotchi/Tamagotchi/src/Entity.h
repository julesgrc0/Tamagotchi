#pragma once
#include<SFML/Graphics.hpp>

enum EntityState {
	STATIC,
	SICK,
	ANGRY,
	LOOP,
	HAPPY,
	ENERGIE,
	WAIT
};

class Entity
{
public:
	Entity();
	~Entity();
	
	EntityState state;
	int8_t state_index;
	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Vector2f size = sf::Vector2f(0,0);

	bool aabb(Entity&);
	static EntityState getStatefromString(std::string);
protected:
	virtual void update(float&);
	virtual void draw(sf::RenderWindow&);
};

