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

    delete[] tmp;    
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

int index = 0;
int g_index = 0;
float upd = 0;

void Window::update(float& deltatime)
{
    upd += deltatime * 1000;
    if (upd >= 50)
    {
        upd = 0;
        index++;
        if (index >= this->entityTextures[0].second[g_index].second.size())
        {
            index = 0;
            g_index++;
            if (g_index >= this->entityTextures[0].second.size())
            {
                g_index = 0;
            }
        }
    }
   
}


void Window::draw(sf::RenderWindow& window)
{
    sf::Sprite s;
    sf::Texture tmp = this->entityTextures[0].second[g_index].second[index];
    s.setTexture(tmp);
    s.setPosition(sf::Vector2f(0, 0));
    s.setScale(sf::Vector2f(4,4));
    window.draw(s);

    
    /*sf::RectangleShape rectangle;
    rectangle.setPosition(sf::Vector2f(100, 100));
    rectangle.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
    rectangle.setFillColor(sf::Color::Red);
    window.draw(rectangle);
        */
}

void Window::init_load()
{

    std::string path(merge_path(this->application_path, FONT));
    if (!this->font.loadFromFile(path))
    {
        LOG() << "[ERR] Fail to load " << path;
        return;
    }
    else {
        LOG() << "[INFO] Load font in " << path;
        this->fontload = true;
    }
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
            LOG() << "[ERR] Fail to load " << path;
            return;
        }
        else {
            LOG() << "[INFO] Load font in " << path;
            this->fontload = true;
        }

        free(string);
    }
    else
    {
        LOG() << "[ERR] Fail to load " << merge_path(this->application_path, FONT);
    }*/



    std::vector<DirectoryItem> items;
    std::vector<std::string> requireTexturesFolders = {
        ANIM_HAPPY ,
        ANIM_ANGRY,
        ANIM_SICK,
        ANIM_WAIT,
        ANIM_LOOP ,
        ANIM_STATIC,
        ANIM_ENERGIE
    };

    std::string assetsDir = merge_path(this->application_path, "assets\\");
    readdir(assetsDir, &items);
    if (items.size() == 0)
    {
        LOG() << "[ERR] No assets files found in " << this->application_path;
        return;
    }

    int ent_id = 0;
    for (DirectoryItem& item : items)
    {
        if (!item.isFile && item.name.rfind("type_", 0) == 0)
        {
            ent_id++;
            

            LOG() << "[INFO] Load entity " + item.name;

            std::vector<DirectoryItem> texturesDir;
            readdir(assetsDir + item.name, &texturesDir);
            if (texturesDir.size())
            {
                int totalSize = 0;
                std::vector<std::string> strlist;
                for (auto& it : texturesDir)
                {
                    if (!it.isFile && it.name != ".." && it.name != ".")
                    {
                        strlist.push_back(it.name);
                    }
                }

                if (contains_list(requireTexturesFolders, strlist))
                {
                    LOG() << "[INFO] All required textures folder found";
                    std::vector< // animation list
                        std::pair<
                        EntityState, // state
                        std::vector<sf::Texture> // state textures
                        >
                    > animation;

                    for (std::string& folder : requireTexturesFolders)
                    {
                        std::string texDir = assetsDir + item.name + "\\" + folder+"\\";
                        LOG() << "[INFO] Load textures from " << texDir;

                        texturesDir.clear();
                        readdir(texDir, &texturesDir);

                        if (texturesDir.size())
                        {
                            std::vector<sf::Texture> ent_textures;
                            for (auto& it : texturesDir)
                            {
                                if (it.isFile && it.name.find(".png"))
                                {
                                    sf::Texture tmp;
                                    if (tmp.loadFromFile(texDir+ it.name))
                                    {
                                        totalSize += it.lowPart;
                                        LOG() << "[INFO] Textures " << it.name << " " << it.lowPart << "o";
                                        ent_textures.push_back(tmp);
                                    }
                                }
                            }

                            animation.push_back(std::make_pair(Entity::getStatefromString(folder), ent_textures));
                        }else
                        {
                            LOG() << "[ERR] Textures no found in " << texDir;
                        }
                    }

                    std::pair<
                        int, // type id
                        std::vector< // animation list
                        std::pair<
                        EntityState, // state
                        std::vector<sf::Texture> // state textures
                        >
                        >
                    > ent_obj = std::make_pair(ent_id, animation);
                    this->entityTextures.push_back(ent_obj);

                }

                LOG() << "[INFO] " << totalSize / 1000 << " ko of textures have been loaded for "+item.name;
            }
        }
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
    return std::string(path1) + std::string(path2);
}

