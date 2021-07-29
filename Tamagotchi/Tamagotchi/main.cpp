#include<iostream>
#include<SFML/Window.hpp>
#include"src/Game.h"

int main(int argc, char** argv)
{
	sf::err().rdbuf(NULL);
	Window* window =  new Window();
	if (window->start())
	{
		return 0;
	}
	return 1;
}