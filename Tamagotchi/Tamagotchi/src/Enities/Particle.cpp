#include "Particle.h"


Particle::Particle(sf::Texture texture, int id, float angle, float speed, sf::Vector2f position) : Entity({ texture },id)
{
	this->angle = angle;
	this->speed = speed;
	this->position = position;
}

Particle::Particle(int id, float angle, float speed, sf::Vector2f position) : Entity(id)
{
	this->angle = angle;
	this->speed = speed;
	this->position = position;
}

void Particle::update(float& deltatime)
{
	if (!this->stop)
	{
		if (this->decrease)
		{
			this->speed -= deltatime * this->time;
			if (this->speed <= 0)
			{
				this->stop = true;
			}
		}
		this->position.x += this->speed * std::cos(angle) * deltatime;
		this->position.y += this->speed * std::sin(angle) * deltatime;
	}	
}

void Particle::DecreaseSpeed(float time)
{
	this->time = time;
}

bool Particle::isStop()
{
	return this->stop;
}

void Particle::draw(sf::RenderWindow& window)
{
	if (this->textures_list.size())
	{
		sf::Sprite s;
		s.setTexture(this->textures_list[0]);
		s.setPosition(this->position);
		s.setTextureRect(sf::IntRect(0,0, this->size.x,this->size.y));
		window.draw(s);
	}else
	{
		sf::RectangleShape rect;
		rect.setSize(this->size);
		rect.setPosition(this->position);
		rect.setFillColor(this->color);
		window.draw(rect);
	}
}

Particle::~Particle()
{

}