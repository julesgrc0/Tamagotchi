#include<iostream>
#include<SFML/Window.hpp>
#include"src/Game.h"

int main(int argc, char** argv)
{
	sf::err().rdbuf(NULL);
	Window* window =  new Window();
	int type_id = 1;
	if (argc > 1)
	{
		type_id = atoi(argv[1]);
		if (type_id < 1)
		{
			type_id = 1;
		}
	}
	if (window->start(type_id))
	{
		return 0;
	}
	return 1;
}