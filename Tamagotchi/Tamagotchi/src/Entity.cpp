#include "Entity.h"
#include "Const.h"

Entity::Entity(std::vector<std::pair<EntityState, std::vector<sf::Texture>>> textures, int id)
{
    this->textures = textures;
    this->id = id;
}

Entity::Entity(std::vector<sf::Texture> textures, int id)
{
    this->textures_list = textures;
    this->id = id;
}

Entity::Entity(int id)
{
    this->id = id;
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderWindow &)
{
}

void Entity::update(float &)
{
}

bool Entity::aabb(Entity &e)
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

std::string Entity::getStatetoString(EntityState s)
{

    switch (s)
    {
    case ANGRY:

        return ANIM_ANGRY;
        break;
    case ENERGIE:
        return ANIM_ENERGIE;
        break;
    case HAPPY:
        return ANIM_HAPPY;
        break;
    case LOOP:
        return ANIM_LOOP;
        break;
    case SICK:
        return ANIM_SICK;
        break;
    case STATIC:
        return ANIM_STATIC;
        break;
    case WAIT:
        return ANIM_WAIT;
        break;
    case SLEEP:
        return ANIM_SLEEP;
        break;
    }

    return ANIM_STATIC;
}

EntityState Entity::getStatefromString(std::string str)
{
    EntityState s = EntityState::STATIC;
    if (str == ANIM_HAPPY)
    {
        s = EntityState::HAPPY;
    }
    if (str == ANIM_ANGRY)
    {
        s = EntityState::ANGRY;
    }
    if (str == ANIM_SICK)
    {
        s = EntityState::SICK;
    }
    if (str == ANIM_WAIT)
    {
        s = EntityState::WAIT;
    }
    if (str == ANIM_LOOP)
    {
        s = EntityState::LOOP;
    }
    if (str == ANIM_STATIC)
    {
        s = EntityState::STATIC;
    }
    if (str == ANIM_ENERGIE)
    {
        s = EntityState::ENERGIE;
    }

    if (str == ANIM_SLEEP)
    {
        s = EntityState::SLEEP;
    }

    return s;
}