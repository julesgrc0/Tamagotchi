#include "Entity.h"
#include "Const.h"

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

EntityState Entity::getStatefromString(std::string str)
{
    EntityState s;
    if(str == ANIM_HAPPY )
    {
        s = EntityState::HAPPY;
    }
    if(str == ANIM_ANGRY)
    {
        s = EntityState::ANGRY;
    }
    if(str == ANIM_SICK )
    {
        s = EntityState::SICK;
    }
    if(str == ANIM_WAIT )
    {
        s = EntityState::WAIT;
    }
    if(str == ANIM_LOOP )
    {
        s = EntityState::LOOP;
    }
    if(str == ANIM_STATIC )
    {
        s = EntityState::STATIC;
    }
    if(str == ANIM_ENERGIE)
    {
        s = EntityState::ENERGIE;
    }


    return s;
}