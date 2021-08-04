#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Audio.hpp>
#include "Game.h"

#include <Windows.h>
#include <iostream>
#include <thread>

#include "Log.h"
#include "Const.h"
#include "Utils.h"
#include "UserConfig.h"

Window::Window()
{
    this->application_path = new char[MAX_PATH];
    LPWSTR tmp = new WCHAR[MAX_PATH];

    GetModuleFileNameW(NULL, tmp, MAX_PATH);

    this->application_path = _com_util::ConvertBSTRToString(_bstr_t(tmp).GetBSTR());
    std::string tmpstr = this->application_path;

    std::vector<std::string> list = split(tmpstr, '\\');
    list.pop_back();
    //strcpy(this->application_path, (join(list, '\\').c_str()));
    this->application_path = join(list, '\\');
    delete[] tmp;
}

Window::~Window()
{
}

bool Window::start()
{
    this->init_load();
    
    UserConfig* config = new UserConfig(std::string(this->application_path));
    config->loadConfig();
    ConfigObject userconf = config->user;
    
    delete config;

    sf::Music music;
    if (userconf.musicEnable)
    {
        std::string musicpath = this->application_path + "assets\\music\\background.wav";
        if (music.openFromFile(musicpath))
        {
            LOG() << "[INFO] Load background music in " << musicpath;

            music.setPitch(userconf.musicPitch);
            music.setVolume(userconf.musicVolume);

            // TODO: Save in game data before close
            // std::string song_index = std::to_string(music.getPlayingOffset().asSeconds()) + "/" + std::to_string(music.getDuration().asSeconds());
        }
        else
        {
            LOG() << "[ERR] Fail to load background music in " << musicpath;
        }
    }

    if (this->state == WindowState::START_GAME)
    {
       
        this->animal = new Animal(this->entityTextures[0].second, this->entityTextures[0].first);
        this->animal->setIconsPack(this->icons);
        // free unused textures
        //this->entityTextures.clear();
        //this->entityTextures.shrink_to_fit();

        if (userconf.musicEnable)
        {
            music.play();
        }

        float deltatime = 0;

        sf::Clock clock;
        sf::Event event;

        sf::RenderWindow window(sf::VideoMode(300, 300), "Tamagotchi", sf::Style::Close);
        window.setVerticalSyncEnabled(userconf.VerticalSync);
        //sf::Image tmp;
        //tmp.loadFromFile(this->application_path);
        //window.setIcon(tmp.getSize().x, tmp.getSize().y, tmp.getPixelsPtr());
        
        if (userconf.alwaysOnTop)
        {
            HWND hwnd = window.getSystemHandle();
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }

        if (!userconf.console)
        {
            HWND console = GetConsoleWindow();
            ShowWindow(console, SW_HIDE);
        }
        
        /*std::thread([&]() {
            float lastdelta = 0;
            while (window.isOpen())
            {
                
                if (deltatime != lastdelta)
                {
                    lastdelta = deltatime;
                    this->update(deltatime);
                }
            }
        }).detach();
        */
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

            if (userconf.showFPS)
            {
                // render time (deltatime * std::pow(10, 3)) 
                window.setTitle(std::string("Tamagotchi " + std::to_string(1.0 / deltatime)).c_str());
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

void Window::update(float &deltatime)
{
    this->animal->update(deltatime);
}

void Window::draw(sf::RenderWindow &window)
{
    if (this->animal->getBackground() != this->animal_back_index )
    {
        this->animal_back_index = this->animal->getBackground();
        this->animal_background.setTexture(this->background[this->animal->getBackground()]);
        this->animal_background.setPosition(sf::Vector2f(0, 0));
        this->animal_background.setScale(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
    }
    window.draw(this->animal_background);

    this->animal->draw(window);

    if (this->animal->isNight())
    {
        sf::RectangleShape filter;
        filter.setFillColor(sf::Color::Color(12, 32, 145, 100));
        filter.setPosition(sf::Vector2f(0, 0));
        filter.setSize(sf::Vector2f(window.getSize()));
        window.draw(filter);
    }
   

    
    /*
   sf::Sprite s;
    s.setTexture(this->icons[0]);
    s.setPosition(sf::Vector2f(10, 10));
    window.draw(s);
    
     sf::Sprite s;
    sf::Texture tmp = this->entityTextures[0].second[g_index].second[index];
    s.setTexture(tmp);
    s.setPosition(sf::Vector2f(0, 0));
    s.setScale(sf::Vector2f(4,4));
    window.draw(s);
    */
    /*sf::RectangleShape rectangle;
    rectangle.setPosition(sf::Vector2f(100, 100));
    rectangle.setSize(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
    rectangle.setFillColor(sf::Color::Red);
    window.draw(rectangle);
        */
}

void Window::init_load()
{

    std::string path(this->application_path+FONT);
    if (!this->font.loadFromFile(path))
    {
        LOG() << "[ERR] Fail to load " << path;
        return;
    }
    else
    {
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
        ANIM_HAPPY,
        ANIM_ANGRY,
        ANIM_SICK,
        ANIM_WAIT,
        ANIM_LOOP,
        ANIM_STATIC,
        ANIM_ENERGIE};

    std::string assetsDir = this->application_path+ "assets\\";
    readdir(assetsDir, &items);
    if (items.size() == 0)
    {
        LOG() << "[ERR] No assets files found in " << this->application_path;
        return;
    }

    int ent_id = 0;
    for (DirectoryItem &item : items)
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
                for (auto &it : texturesDir)
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
                            EntityState,             // state
                            std::vector<sf::Texture> // state textures
                            >>
                        animation;

                    for (std::string &folder : requireTexturesFolders)
                    {
                        std::string texDir = assetsDir + item.name + "\\" + folder + "\\";
                        LOG() << "[INFO] Load textures from " << texDir;

                        texturesDir.clear();
                        readdir(texDir, &texturesDir);

                        if (texturesDir.size())
                        {
                            std::vector<sf::Texture> ent_textures;
                            for (auto &it : texturesDir)
                            {
                                if (it.isFile && it.name.find(".png"))
                                {
                                    sf::Texture tmp;
                                    if (tmp.loadFromFile(texDir + it.name))
                                    {
                                        totalSize += it.lowPart;
                                        LOG() << "[INFO] Textures " << it.name << " " << it.lowPart << "o";
                                        ent_textures.push_back(tmp);
                                    }
                                }
                            }

                            animation.push_back(std::make_pair(Entity::getStatefromString(folder), ent_textures));
                        }
                        else
                        {
                            LOG() << "[ERR] Textures no found in " << texDir;
                        }
                    }

                    std::pair<
                        int,         // type id
                        std::vector< // animation list
                            std::pair<
                                EntityState,             // state
                                std::vector<sf::Texture> // state textures
                                >>>
                        ent_obj = std::make_pair(ent_id, animation);
                    this->entityTextures.push_back(ent_obj);
                }

                LOG() << "[INFO] " << totalSize / 1000 << " ko of textures have been loaded for " + item.name;
            }
        }
        else if (!item.isFile && item.name == "backgrounds")
        {
            this->textureLoader(item.name, &this->background, assetsDir);
        }
        else if (!item.isFile && item.name == "icons")
        {
            this->textureLoader(item.name, &this->icons, assetsDir);
        }
    }
    this->state = WindowState::START_GAME;
}

void Window::textureLoader(std::string name, std::vector<sf::Texture> *textures, std::string dir)
{
    std::vector<DirectoryItem> list;
    readdir(dir + "\\" + name, &list);
    int totalsize = 0;

    if (list.size())
    {
        for (DirectoryItem &it : list)
        {
            if (it.isFile && it.name.find(".png"))
            {
                sf::Texture tmp;
                if (tmp.loadFromFile(dir + "\\" + name + "\\" + it.name))
                {
                    totalsize += it.lowPart;
                    LOG() << "[INFO] Textures " << it.name << " " << it.lowPart << "o";
                    textures->push_back(tmp);
                }
            }
        }
    }
    else
    {
        LOG() << "[ERR] Textures for " << name << " are not found in " << dir + "\\" + name;
    }

    LOG() << "[INFO] " << totalsize / 1000 << " ko of " << name << " textures have been loaded";
}

sf::Text Window::text(std::string text, sf::Vector2f position, int size, bool diff)
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