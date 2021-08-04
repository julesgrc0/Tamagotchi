#pragma once
#include<SFML/Graphics.hpp>
#include "../Entity.h"

class Particle : public Entity
{
public:
	Particle(sf::Texture texture, int id, float angle, float speed, sf::Vector2f position);
	Particle(int id, float angle, float speed, sf::Vector2f position);
	~Particle();

	

	void update(float&) override;
	void draw(sf::RenderWindow&) override;
	void  DecreaseSpeed(float time);
	bool isStop();

	sf::Vector2f size;
	sf::Color color;
private:
	float time;
	bool stop = false;
	bool decrease = false;
	float speed = 0;
};

