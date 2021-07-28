#pragma once
#include<SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	~Entity();
	
	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Vector2f size = sf::Vector2f(0,0);

	bool aabb(Entity&);
protected:
	virtual void update(float&);
	virtual void draw(sf::RenderWindow&);
};

