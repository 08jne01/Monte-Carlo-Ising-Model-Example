#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "Grid.h"


class Program

{
public:

	Program(int w, int h);
	int mainLoop();
	void keyCallback(sf::Event events);
	void draw();
	void update();
private:
	int width, height;
	sf::RenderWindow window;
	Grid grid;
};