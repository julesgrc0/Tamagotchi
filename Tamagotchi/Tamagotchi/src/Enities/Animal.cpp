#include "Animal.h"
#include "../Log.h"
#include"../Const.h"

Animal::Animal(std::vector<std::pair<EntityState, std::vector<sf::Texture>>> t, int id) : Entity(t, id)
{
    this->state = EntityState::WAIT;
    this->updateCurrentTextures();
}

void Animal::update(float &detatime)
{
    if (this->alive)
    {

        this->animation_time += detatime * 1000;
        this->background_time += detatime * 1000;
        this->night_time += detatime * 1000;
        this->global_time += detatime * 1000;
        this->interaction_time += detatime * 1000;
        this->hunger_time += detatime * 1000;


        if (this->state == EntityState::WAIT)
        {
            if (this->animation_time >= 200)
            {
                this->animation_time = 0;
                this->texturesIndex++;
                this->stateChange = true;
                if (this->texturesIndex >= this->currentTextures.size())
                {
                    this->texturesIndex = 0;
                }
            }
        }
        


        if (this->hunger_time >= SHOW_HUNGER_TIME)
        {
            this->showHunger = true;
            this->hunger -= detatime;

            if (this->hunger + this->eat_action >= 100)
            {
                this->showHunger = false;
                this->hunger_time = 0;
                this->eat_action = 0;
                this->hunger = MAX_VITAL;
            }

            if (this->hunger <= 0)
            {
                this->showHunger = false;
                this->hunger_time = 0;
                this->eat_action = 0;
                this->hunger = MAX_VITAL;
                this->life--;
            }
        }

        if (this->life == 0)
        {
            this->alive = false;
        }

        if (this->night_time >= 60 * 60 * 1000) // 1H
        {
            this->switch_night_count++;
            this->night = !this->night;
            this->night_time = 0;

            if (this->switch_night_count >= 24) // 1 day
            {
                this->switch_night_count = 0;
                this->max_background += 3;
                if (this->max_background >= BACKGROUND_TOTAL)
                {
                    this->max_background = 0;
                }
            }
        }

        if (this->background_time >= 500)
        {
            this->background_time = 0;
            this->background_index++;
            if (this->background_index >= this->max_background + BACKGROUND_MAX_FRAMES)
            {
                this->background_index = this->max_background;
            }
        }
    }
}

void Animal::updateCurrentTextures()
{
    std::pair<EntityState, std::vector<sf::Texture>> item;

    std::find_if(this->textures.begin(), this->textures.end(), [&](const std::pair<EntityState, std::vector<sf::Texture>>& p)
        {
            if (p.first == this->state)
            {
                item = p;
                return true;
            }
            return false;
        });
    this->currentTextures = item.second;
}

void Animal::draw(sf::RenderWindow &window)
{
    if (this->alive)
    {
        if (this->stateChange)
        {
            this->currentSprite.setTexture(this->currentTextures[this->texturesIndex]);
            this->currentSprite.setScale(sf::Vector2f(4, 4));
            this->currentSprite.setOrigin(sf::Vector2f(ANIMAL_TEXTURE_SIZE / 2, ANIMAL_TEXTURE_SIZE / 2));

            if (!this->isCenter)
            {
                this->isCenter = true;
                this->position.x = (window.getSize().x - ANIMAL_TEXTURE_SIZE) / 2;
                this->position.y = ((window.getSize().y - ANIMAL_TEXTURE_SIZE) / 2) + 18 * PIXEL_SIZE;
            }
            this->currentSprite.setPosition(this->position);
            this->stateChange = false;
        }
        
        window.draw(this->currentSprite);
    }

    if (this->showBox)
    {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(ANIMAL_TEXTURE_SIZE * 4, ANIMAL_TEXTURE_SIZE * 4));
        rect.setPosition(this->position);
        rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));

        rect.setOutlineColor(sf::Color::Red);
        rect.setOutlineThickness(1);
        rect.setFillColor(sf::Color::Transparent);
        window.draw(rect);
    }
}

void Animal::hud(sf::RenderWindow& window)
{
    
}

bool Animal::isNight()
{
    return this->night;
}

int Animal::getBackground()
{
    return this->background_index;
}