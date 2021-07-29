#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"

#include <Windows.h>
#include <iostream>
#include <thread>

#include "Log.h"
#include "Const.h"
#include "Utils.h"


Window::Window()
{
    this->application_path = new char[MAX_PATH];
    LPWSTR tmp = new WCHAR[MAX_PATH];
    
    GetModuleFileNameW(NULL, tmp, MAX_PATH);
    
    this->application_path = _com_util::ConvertBSTRToString(_bstr_t(tmp).GetBSTR());
    std::string tmpstr = this->application_path;

    std::vector<std::string> list = split(tmpstr, '\\');
    list.pop_back();
    strcpy(this->application_path, (join(list, '\\').c_str()));

    //delete[] tmp;    
}

Window::~Window()
{
}


bool Window::start()
{

    sf::RenderWindow window(sf::VideoMode(300, 300), "Tamagotchi", sf::Style::Close);

    sf::Clock clock;
    sf::Event event;
    float deltatime = 0;
    this->init_load();

    if (this->state == WindowState::START_GAME)
    {
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

            window.setTitle(std::string("Tamagotchi " + std::to_string(1.0 / deltatime)).c_str());
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
}

void Window::init_load()
{
    
    //std::string path(merge_path(this->application_path, FONT));
    
    /*FILE* f = fopen(path.c_str(), "rb");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        unsigned char* string = (unsigned char*)malloc(fsize + 1);
        fread(string, fsize, 1, f);
        fclose(f);

        if (!this->font.loadFromMemory(string, fsize))
        {
            LOG() << "[ERR] Fail to load " << merge_path(this->application_path, FONT);
            return;
        }
        else {
            this->fontload = true;
        }

        free(string);
    }else
    {
        LOG() << "[ERR] Fail to load " << merge_path(this->application_path, FONT);
    }*/
    

 
    std::vector<DirectoryItem> items;
    readdir(std::string(this->application_path) + "\\assets\\", &items);
    if (items.size() == 0)
    {
        LOG() << "[ERR] No assets files found in " << this->application_path;
        return;
    }

    for (DirectoryItem& item : items)
    {
        
        LOG() << item.name << " " << item.lowPart;
    }
    this->state = WindowState::START_GAME;
}



sf::Text Window::text(std::string text, sf::Vector2f position, int size,bool diff)
{
    sf::Text t;
    t.setFont(this->font);
    t.setString(text); 
    t.setCharacterSize(size);

    if (diff)
    {
        position.x -= t.getLocalBounds().width;
        position.y -= t.getLocalBounds().height;
    }

    t.setPosition(position);
    t.setFillColor(sf::Color::White);
    return t;
}

std::string merge_path(const char* path1, const char* path2)
{
    char* merge = new char[sizeof(path1)];
    merge = strcpy(merge, path1);
    std::string result(strcat(merge, (char*)path2));

    return result;
}

