#include "Grid.h"

Grid::Grid(int w, int h) : width(w), height(h), temp(15), curTime(-2), drawTime(w*h), gen(1), coupleJ(5e-23)

{
	srand(10);
	rand();

	for (int i = 0; i < w; i++)

	{
		std::vector<int> buffer;
		for (int j = 0; j < h; j++)

		{
			buffer.push_back(random(0.5));
		}
		gridValues.push_back(buffer);
	}
}

double Grid::energy(Vec2 pos_, int spin)

{
	int up, down, left, right, iUp, iDown, iLeft, iRight;

	Vec2 pos = pos_;

	iUp = pos.y - 1;
	iDown = pos.y + 1;
	iLeft = pos.x - 1; 
	iRight = pos.x + 1;


	//if (pos.x > width - 2) iRight = 0;
	//if (pos.x < 1) iLeft = width - 1;
	//if (pos.y > height - 2) iDown = 0;
	//if (pos.y < 1) pos.y = iUp = height - 1;
	if (pos.x > width - 2) iRight = width - 3;
	if (pos.x < 1) iLeft = 1;
	if (pos.y > height - 2) iDown = height - 3;
	if (pos.y < 1) pos.y = iUp = 1;

	up = gridValues[pos.x][iUp];
	down = gridValues[pos.x][iDown];
	left = gridValues[iLeft][pos.y];
	right = gridValues[iRight][pos.y];

	return -coupleJ * spin * (up + down + left + right);
}

void Grid::flip()

{
	int x, y;
	x = rand() % (width);
	y = rand() % (height);

	Vec2 pos(x, y);
	int spin = gridValues[pos.x][pos.y];
	eCur = energy(pos, spin);
	eTrial = energy(pos, -spin);

	double r = exp(-(eTrial - eCur) / (K_BOLTZ*temp));
	//std::cout << -(eTrial - eCur) / (K_BOLTZ*temp) << std::endl;
	if (r > 1)

	{
		gridValues[pos.x][pos.y] = -spin;
	}

	else

	{
		gridValues[pos.x][pos.y] = spin * random(r);
	}

	curTime++;
}

double Grid::mag()

{
	std::vector<std::vector<int>> buffer = gridValues;
	double total = 0;

	for (int i = 0; i < buffer.size(); i++)

	{
		for (int j = 0; j < buffer[i].size(); j++)

		{
			total += (double)buffer[i][j];
		}
	}

	return total / (width*height);
}

void Grid::draw(sf::RenderWindow& window)

{
	if (curTime > drawTime || curTime < 0)

	{
		std::cout << "Generation: " << gen << std::endl;
		std::cout << "Temp: " << temp << std::endl;
		std::cout << "Magnetisation: " << mag() << std::endl;
		gen++;
		vertices.clear();

		std::vector<std::vector<int>> buffer = gridValues;

		for (int i = 0; i < buffer.size(); i++)

		{
			for (int j = 0; j < buffer[i].size(); j++)

			{
				int spin = buffer[i][j];
				spin += 1;
				spin /= 2;
				vertices.append(sf::Vertex(sf::Vector2f(i, j), sf::Color(spin * 255, spin * 255, spin * 255, 255)));
			}
		}
		curTime = 0;
		//temp -= 0.01*(temp);
		if (direction == 1)

		{
			temp += 0.01;
		}

		else if (direction == -1)

		{
			temp -= 0.001*temp;
		}
	}

	window.draw(vertices);
}

int Grid::random(double probability)

{
	int number = rand() % (10000 + 1);
	double value = (double)number / 10000.0;
	if (value < probability)

	{
		return -1;
	}

	else

	{
		return 1;
	}
}