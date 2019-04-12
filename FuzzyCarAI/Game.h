#pragma once
/** SFML INCLUDES */
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

/** OUR CLASSES */
#include "Input.h"
#include "StaticSprite.h"

class Game
{
public:
	Game(sf::RenderWindow* hwnd, Input* in);
	~Game();

	void update(float* delta);
	void render();

protected:
	// Window and input objects
	sf::RenderWindow* window;
	Input* input;
	// Background
	StaticSprite backgroundSP;
	sf::Texture backgroundTX;
	// Player 1 sprite
	StaticSprite playerSP;
	sf::Texture playerTX;
	// Player 2 sprite
	StaticSprite player2SP;
	sf::Texture player2TX;
};
