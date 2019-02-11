#include "Program.h"

Program::Program(int w, int h) : width(w), height(h), window(sf::VideoMode(w, h), "Spin Calculation"), grid(w, h)

{

}

int Program::mainLoop()

{

	sf::Clock clock;
	sf::Event events;

	if (!window.isOpen())

	{
		return EXIT_FAILURE;
	}

	std::thread calculation

	{
		[&]()

		{
			while (window.isOpen())

			{
				update();
			}
		}
	};

	calculation.detach();

	while (window.isOpen())

	{
		while (window.pollEvent(events))

		{
			if (events.type == sf::Event::EventType::Closed)

			{
				window.close();
			}

			keyCallback(events);
		}

		window.clear(sf::Color::Black);

		draw();

		window.display();
	}
	return EXIT_SUCCESS;
}

void Program::draw()

{
	grid.draw(window);
}

void Program::update()

{
	grid.flip();
}

void Program::keyCallback(sf::Event events)

{
	if (events.type == sf::Event::EventType::KeyPressed)

	{
		switch (events.key.code) 

		{
			case sf::Keyboard::Left:

			{
				grid.direction = -1;
				break;
			}

			case sf::Keyboard::Right:

			{
				grid.direction = 1;
				break;
			}

			case sf::Keyboard::Down:

			{
				grid.direction = 0;
				break;
			}
		}
	}
}