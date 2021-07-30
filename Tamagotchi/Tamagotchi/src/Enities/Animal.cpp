#include "Animal.h"
#include"../Log.h"
Animal::Animal(std::vector<std::pair<EntityState, std::vector<sf::Texture>>> t, int id) : Entity(t,id)
{
    this->state = EntityState::ANGRY;
}

void Animal::update(float& detatime)
{
    this->time += detatime * 1000;
    if (this->time >= 1000)
    {
        
        this->time = 0;
        int s = (this->state + 1);
        if (s >= 7)
        {
            s = 0;
        }
        this->state = (EntityState)s;
        LOG() << Entity::getStatetoString(this->state);
    }

    

}

void Animal::draw(sf::RenderWindow& window)
{
    sf::Sprite s;
    std::pair<EntityState, std::vector<sf::Texture>> item;
    
    std::find_if(this->textures.begin(), this->textures.end(), [&](const std::pair<EntityState, std::vector<sf::Texture>>& p) {
        if (p.first == this->state)
        {
            item = p;
            return true;
        }
        return false;
    });

    sf::Texture tmp = item.second[0];
    s.setTexture(tmp);
    s.setPosition(this->position);
    s.setScale(sf::Vector2f(4, 4));
    s.setOrigin(sf::Vector2f(tmp.getSize().x / 2, tmp.getSize().y / 2));
    window.draw(s);

   
    this->position.x = (window.getSize().x - tmp.getSize().x) / 2;
    this->position.y = (window.getSize().y - tmp.getSize().y) / 2;

    /*
    
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(tmp.getSize().x*4, tmp.getSize().y*4));
    rect.setPosition(this->position);
    rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));

    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1);
    rect.setFillColor(sf::Color::Transparent);
    window.draw(rect);
    */
}