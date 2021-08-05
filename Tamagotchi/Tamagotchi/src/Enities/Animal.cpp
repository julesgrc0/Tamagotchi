#include "Animal.h"
#include "../Log.h"

#include "../Const.h"

Animal::Animal(std::vector<std::pair<EntityState, std::vector<sf::Texture>>> t, int id) : Entity(t, id)
{
    this->setState(EntityState::WAIT, 200);
}

void Animal::update(float &deltatime)
{
    if (this->alive)
    {

        this->animation_time += deltatime * 1000;
        this->background_time += deltatime * 1000;
        this->night_time += deltatime * 1000;
        this->global_time += deltatime * 1000;
        this->interaction_time += deltatime * 1000;
        this->hunger_time += deltatime * 1000;

        if (this->waitfor_eat >= 0)
        {
            this->waitfor_eat -= deltatime * 1000;
        }
        if (this->waitfor_play >= 0)
        {
            this->waitfor_play -= deltatime * 1000;
        }

        if (this->animation_time >= this->current_animation_speed)
        {
            this->animation_time = 0;
            this->texturesIndex++;
            this->stateChange = true;
            if (this->texturesIndex >= this->currentTextures.size())
            {
                if (this->state == EntityState::ANGRY)
                {
                    this->setState(EntityState::WAIT, 200);
                }

                if (this->state == EntityState::LOOP)
                {
                    this->setState(EntityState::WAIT, 200);
                }

                if (this->state == EntityState::HAPPY)
                {
                    this->setState(EntityState::ENERGIE, 200);
                }
                this->texturesIndex = 0;
            }
        }

        bool mousepress = false;
        for (size_t i = 0; i < 5; i++)
        {
            if (sf::Mouse::isButtonPressed((sf::Mouse::Button)i))
            {
                mousepress = true;
                if (this->state == EntityState::WAIT)
                {
                    this->setState(EntityState::STATIC, 300);
                }
                break;
            }
        }

        if (!mousepress && this->state == EntityState::STATIC)
        {
            this->setState(EntityState::WAIT, 200);
        }

        this->play_keypress = false;
        if (!(this->waitfor_play >= 0))
        {
            int keycount = 0;
            for (int i = 0; i < 26; i++)
            {
                if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
                {
                    this->play_keypress = true;
                    this->play_key_time += deltatime * 1000;
                    if (this->play_key_time >= 10000)
                    {
                        if (this->state == EntityState::WAIT)
                        {
                            this->setState(EntityState::ENERGIE, 200);
                        }
                        else if (this->state == EntityState::ENERGIE)
                        {
                            this->setState(EntityState::WAIT, 200);
                        }
                        else if (this->state == EntityState::SICK)
                        {
                            this->sick_help_count++;
                            if (this->sick_help_count >= 5)
                            {
                                this->sick_total_count++;
                                this->sick_help_count = 0;

                                if (this->sick_total_count >= 2 || rand() % 100 > 80)
                                {
                                    this->sick_total_count = 0;
                                    this->setState(EntityState::ANGRY, 200);
                                }
                                else
                                {
                                    this->setState(EntityState::WAIT, 200);
                                }
                            }
                        }
                        this->play_key_time = 0;
                        this->play_count++;
                        if (this->play_count >= 4)
                        {
                            this->waitfor_play = 1000 * 60;
                            this->play_count = 0;
                        }
                    }

                    keycount++;
                    if (keycount >= 3)
                    {
                        break;
                    }
                }
            }
            if (!this->play_keypress)
            {
                this->play_key_time = 0;
            }
        }

        this->eat_keypress = false;
        if (!(this->waitfor_eat >= 0) && this->state != EntityState::SICK)
        {
            int keycount = 0;
            for (int i = 26; i < 36; i++)
            {
                if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
                {
                    this->eat_keypress = true;
                    this->eat_key_time += deltatime * 1000;
                    if (this->eat_key_time >= 10000)
                    {
                        this->eat_key_time = 0;
                        this->eat_count++;
                        if (this->showHunger)
                        {
                            this->eat_action += 25;
                        }

                        if (this->eat_count >= 4)
                        {
                            this->waitfor_eat = 1000 * 60;
                            this->eat_count = 0;
                            this->waitfor_eat_count++;
                            if (this->waitfor_eat_count >= 4)
                            {
                                this->waitfor_eat_count = 0;
                                this->setState(EntityState::SICK, 400);
                            }
                        }
                    }

                    keycount++;
                    if (keycount >= 4)
                    {
                        break;
                    }
                }
            }
            if (!this->eat_keypress)
            {
                this->eat_key_time = 0;
            }
        }

        if (this->hunger_time >= SHOW_HUNGER_TIME)
        {
            this->showHunger = true;
            this->hunger -= deltatime;

            if (this->hunger + this->eat_action >= 100)
            {
                this->showHunger = false;
                this->hunger_time = 0;
                this->eat_action = 0;
                this->hunger = MAX_VITAL;

                if (rand() % 100 < 80)
                {
                    this->setState(EntityState::LOOP, 80);
                }
                else
                {
                    this->setState(EntityState::HAPPY, 150);

                    for (size_t i = 0; i < 500; i++)
                    {
                        int speed = (rand() % (180 - 80 + 1)) + 80;
                        int x = (rand() % (300 - 1 + 1)) + 1;
                        int y = (rand() % (100 - 1 + 1)) + 1;
                        y -= 60;

                        Particle p = Particle(i, 90 * 3.14 / 180, speed, sf::Vector2f(x, y));
                        p.DecreaseSpeed(40);
                        p.color = sf::Color(241, 128, 12);
                        p.size = sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE);

                        this->particles.push_back(p);
                    }
                }
            }

            if (this->hunger <= 0)
            {
                this->showHunger = false;
                this->hunger_time = 0;
                this->eat_action = 0;
                this->hunger = MAX_VITAL;
                this->life--;

                if (rand() % 100 > 60)
                {
                    this->sick_total_count = 0;
                    this->setState(EntityState::ANGRY, 200);
                }
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

        if (this->particles.size())
        {

            for (size_t i = 0; i < this->particles.size(); i++)
            {
                if (this->particles[i].isStop())
                {
                    this->particles.erase(this->particles.begin() + i);
                    i--;
                }
                else
                {
                    this->particles[i].update(deltatime);
                }
            }
        }
    }
}

void Animal::setIconsPack(std::vector<sf::Texture> t)
{
    this->icons = t;
}

void Animal::updateCurrentTextures()
{
    std::pair<EntityState, std::vector<sf::Texture>> item;
    this->currentTextures.clear();
    std::find_if(this->textures.begin(), this->textures.end(), [&](const std::pair<EntityState, std::vector<sf::Texture>> &p)
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
void Animal::setState(EntityState state, float speed)
{
    this->current_animation_speed = speed;
    this->state = state;
    this->updateCurrentTextures();
    this->stateChange = true;
    this->texturesIndex = 0;
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

        if (this->play_keypress)
        {
            sf::RectangleShape rect;
            rect.setOutlineColor(sf::Color::Color(40, 40, 40));
            rect.setOutlineThickness(1);
            rect.setSize(sf::Vector2f(5, (window.getSize().y / 3) / PIXEL_SIZE));

            rect.setFillColor(sf::Color::Transparent);
            rect.setPosition(sf::Vector2f((5 * PIXEL_SIZE), (window.getSize().y - (rect.getSize().y + 40)) / PIXEL_SIZE));
            rect.setScale(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));

            window.draw(rect);

            rect.setOutlineColor(sf::Color::Transparent);
            rect.setOutlineThickness(0);
            rect.setSize(sf::Vector2f(rect.getSize().x, (rect.getSize().y * this->play_key_time) / 10000));
            if (this->play_key_time >= 10000 / 2)
            {
                rect.setFillColor(sf::Color(255 - ((this->play_key_time / 2) * 255 / (10000 / 2)) * 2, 255, 0));
            }
            else
            {
                rect.setFillColor(sf::Color(255, ((this->play_key_time / 2) * 255 / (10000 / 2)) * 2, 0));
            }
            window.draw(rect);

            sf::Sprite s;
            s.setTexture(this->icons[IconType::BALL]);
            s.setPosition(sf::Vector2f(rect.getPosition().x, rect.getPosition().y + (window.getSize().y / 3) + PIXEL_SIZE));
            s.setScale(sf::Vector2f(1.2, 1.2));
            window.draw(s);
        }

        if (this->eat_keypress)
        {
            sf::RectangleShape rect;
            rect.setOutlineColor(sf::Color::Color(40, 40, 40));
            rect.setOutlineThickness(1);
            rect.setSize(sf::Vector2f(5, (window.getSize().y / 3) / PIXEL_SIZE));

            rect.setFillColor(sf::Color::Transparent);
            rect.setPosition(sf::Vector2f((window.getSize().x - (10 * PIXEL_SIZE)), (window.getSize().y - (rect.getSize().y + 40)) / PIXEL_SIZE));
            rect.setScale(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));

            window.draw(rect);

            rect.setOutlineColor(sf::Color::Transparent);
            rect.setOutlineThickness(0);
            rect.setSize(sf::Vector2f(rect.getSize().x, (rect.getSize().y * this->eat_key_time) / 10000));
            if (this->eat_key_time >= 10000 / 2)
            {
                rect.setFillColor(sf::Color(255 - ((this->eat_key_time / 2) * 255 / (10000 / 2)) * 2, 255, 0));
            }
            else
            {
                rect.setFillColor(sf::Color(255, ((this->eat_key_time / 2) * 255 / (10000 / 2)) * 2, 0));
            }
            window.draw(rect);

            sf::Sprite s;
            s.setTexture(this->icons[IconType::FOOD]);
            s.setPosition(sf::Vector2f(rect.getPosition().x, rect.getPosition().y + (window.getSize().y / 3) + PIXEL_SIZE));
            s.setScale(sf::Vector2f(1.5, 1.5));
            window.draw(s);
        }

        if (this->particles.size())
        {
            for (size_t i = 0; i < this->particles.size(); i++)
            {

                if (this->particles[i].position.y > window.getSize().y)
                {
                    this->particles.erase(this->particles.begin() + i);
                    i--;
                    LOG() << this->particles.size();
                }
                else
                {
                    this->particles[i].draw(window);
                }
            }
        }
    }

    int index = 0;
    for (size_t i = 0; i < this->icons.size(); i++)
    {
        IconType type = (IconType)i;

        if (type != IconType::MENU && type != IconType::MENU_ACTIVE)
        {
            sf::Sprite s;
            s.setTexture(this->icons[i]);
            s.setScale(sf::Vector2f(1.2, 1.2));
            s.setPosition(sf::Vector2f(index * (s.getGlobalBounds().width + 5) + 2, 2));

            bool draw = false;
            switch (type)
            {
            case COIN:
                if (this->state == EntityState::LOOP)
                {
                    draw = true;
                }
                break;
            case FOOD:
                if (this->showHunger)
                {
                    draw = true;
                }
                break;
            case GAME:
                //
                break;
            case BALL:
                if (this->state == EntityState::ENERGIE || this->state == EntityState::WAIT)
                {
                    draw = true;
                }
                break;
            case VIRUS:
                if (this->state == EntityState::SICK)
                {
                    draw = true;
                }
                break;
            case SLEEP:
                if (this->night)
                {
                    draw = true;
                }
                break;
            case SUN:
                if (!this->night)
                {
                    draw = true;
                }
                break;
            }

            if (draw)
            {
                window.draw(s);
                index++;
            }
        }
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

void Animal::backupState(AnimalSaveState save)
{
    this->texturesIndex = save.texturesIndex;

    this->global_time = save.global_time;

    this->interaction_time = save.interaction_time;
    this->animation_time = save.animation_time;
    this->background_time = save.background_time;
    this->night_time = save.night_time;
    this->hunger_time = save.hunger_time;

    this->current_animation_speed = save.current_animation_speed;

    this->waitfor_play = save.waitfor_play;
    this->waitfor_eat = save.waitfor_eat;

    this->waitfor_eat_count  = save.waitfor_eat_count ;

    this->play_key_time = save.play_key_time;
    this->play_keypress  = save.play_keypress ;

    this->play_count  = save.play_count;

    this->eat_key_time = save.eat_key_time;
    this->eat_keypress  = save.eat_keypress ;

    this->eat_count  = save.eat_count ;

    this->night = save.night;
    this->showBox  = save.showBox ;
    this->showHunger = save.showHunger;

    this->switch_night_count = save.switch_night_count;

    this->background_index  = save.background_index ;
    this->max_background  = save.max_background ;

    this->eat_action  = save.eat_action;

    this->sick_help_count  = save.sick_help_count ;
    this->sick_total_count  = save.sick_total_count ;

    this->hunger  = save.hunger ;
    this->life  = save.life ;
    this->alive  = save.alive ;

    this->stateChange = save.stateChange;

    this->setState((EntityState)save.state, save.current_animation_speed);
}

AnimalSaveState Animal::getBackupState()
{
    AnimalSaveState save;
    save.texturesIndex = this->texturesIndex;

    save.global_time = this->global_time;
    save.interaction_time = this->interaction_time;
    save.animation_time = this->animation_time;
    save.background_time = this->background_time;
    save.night_time = this->night_time;
    save.hunger_time = this->hunger_time;

    save.current_animation_speed = this->current_animation_speed;

    save.waitfor_play = this->waitfor_play;
    save.waitfor_eat = this->waitfor_eat;

    save.waitfor_eat_count = this->waitfor_eat_count;

    save.play_key_time = this->play_key_time;
    save.play_keypress = this->play_keypress;

    save.play_count = this->play_count;

    save.eat_key_time = this->eat_key_time;
    save.eat_keypress = this->eat_keypress;

    save.eat_count = this->eat_count;

    save.night = this->night;
    save.showBox = this->showBox;
    save.showHunger = this->showHunger;

    save.switch_night_count = this->switch_night_count;

    save.background_index = this->background_index;
    save.max_background = this->max_background;

    save.eat_action = this->eat_action;

    save.sick_help_count = this->sick_help_count;
    save.sick_total_count = this->sick_total_count;

    save.hunger = this->hunger;
    save.life = this->life;
    save.alive = this->alive;

    save.stateChange = this->stateChange;

    save.state = (int)this->state;

    return save;
}

bool Animal::isNight()
{
    return this->night;
}

int Animal::getBackground()
{
    return this->background_index;
}