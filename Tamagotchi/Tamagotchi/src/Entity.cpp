#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::draw(sf::RenderWindow&)
{

}

void Entity::update(float&)
{

}

bool Entity::aabb(Entity& e)
{
    if (e.position.x < this->position.x + this->position.x &&
        e.position.x + e.position.x > this->position.x &&
        e.position.y < this->position.y + this->position.y &&
        e.position.y + e.position.y > this->position.y)
    {
        return true;
    }
	return false;
}