/** SFML INCLUDES */
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

/** STANDARD LIBRARY INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <thread>
#include <string>
#include <iostream>

/** OUR CLASSES */
#include "Input.h"
#include "Game.h"
#include "cmake\&{PROJECT_BINARY_DIR}\FuzzyCarAIConfig.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "%s Version %d.%d\n",
			argv[0],
			FuzzyCar_VERSION_MAJOR,
			FuzzyCar_VERSION_MINOR);
		fprintf(stdout, "Usage: %s number\n", argv[0]);
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "FuzzyTheSmartCar!");

	// Setup input and game object from our classes
	Input input;
	Game game(&window, &input);

	// To fix the window view
	sf::View fixed = window.getView();

	// Setup sf::Clock object and delta time float for handline time in our application
	sf::Clock clock;
	float deltaTime;

	while (window.isOpen())
	{
		window.setView(fixed);
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				break;
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
			default:
				// don't handle other events
				break;
			}
		}

		deltaTime = clock.getElapsedTime().asMilliseconds();
		game.update(&deltaTime); //update game
		game.render(); //render game
	}

	return 0;
}