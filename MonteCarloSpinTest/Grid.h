#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Vector2.h"

#define K_BOLTZ 1.381e-23

class Grid

{
public:

	Grid(int w, int h);
	void draw(sf::RenderWindow& window);
	int random(double probability);
	void flip();
	double energy(Vec2 pos_, int spin);
	double mag();
	int direction;

private:
	int width, height, drawTime, curTime, gen;
	double coupleJ, eCur, eTrial, temp;
	std::vector<std::vector<int>> gridValues;
	sf::VertexArray vertices;
};