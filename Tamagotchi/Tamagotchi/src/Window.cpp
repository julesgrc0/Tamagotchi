#include "Window.h"
#include <Windows.h>
#include "Log.h"
#include "Const.h"

Window::Window()
{
    this->application_path = new char[MAX_PATH];
    GetModuleFileNameA(NULL, this->application_path, std::ios::binary);
}

Window::~Window()
{
    delete[] this->application_path;
}


bool Window::start()
{
    this->init_load();
    if (this->state == WindowState::LOAD_ASSETS)
    {
        sf::RenderWindow window(sf::VideoMode(100, 100), "Tamagotchi", sf::Style::Close);

        sf::Clock clock;
        sf::Event event;
        float deltatime = 0;

        while (window.isOpen())
        {
            deltatime = clock.restart().asSeconds();


            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            this->update(deltatime);
            window.clear();
            this->draw(window);
            window.display();
        }

        return true;
    }

    return false;
}

void Window::update(float& deltatime)
{
    
}

void Window::draw(sf::RenderWindow& window)
{
    if (this->state == WindowState::LOAD_ASSETS)
    {
        
    }
}

void Window::init_load()
{
    if (!this->font.loadFromFile(join(this->application_path, FONT)))
    {
        LOG() << "[ERR] Fail to load "+ join(this->application_path, FONT);
    }
    else {
        this->state = WindowState::LOAD_ASSETS;
    }
}


void Window::text(std::string text, sf::Vector2f position, int size)
{
    sf::Text t;
    t.setString(text);
    t.setPosition(position);
    t.setCharacterSize(size);
    t.setFont(this->font);
}

std::string join(const char* path1,const char* path2)
{
    return std::string(path1) + std::string(path2);
}