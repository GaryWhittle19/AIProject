/** GAME HEADER */
#include "Game.h"

Game::Game(sf::RenderWindow* hwnd, Input* in)
{
	// Setup access to SFML window and Input class
	window = hwnd;
	input = in;

	// Menu background
	if (!backgroundTX.loadFromFile("graphics/bg.PNG"))
	{
		// error...
	}
	backgroundSP.setSize(sf::Vector2f(800, 600));
	backgroundSP.setTexture(&backgroundTX);

	// Player sprite
	if (!playerTX.loadFromFile("graphics/player1.png"))
	{
		// error...
	}
	playerSP.setSize(sf::Vector2f(160, 120));
	playerSP.setTexture(&playerTX);
	playerSP.setOrigin(80, 60);

	// Player 2 sprite
	if (!player2TX.loadFromFile("graphics/player2.png"))
	{
		// error
	}
	player2SP.setSize(sf::Vector2f(160, 120));
	player2SP.setTexture(&player2TX);
	player2SP.setOrigin(80, 60);

	playerSP.setPosition(266, 100);	
	player2SP.setPosition(532, 500);
}

Game::~Game()
{

}

void Game::update(float* delta)
{
	render();
}

void Game::render()
{
	window->clear(sf::Color::White);

	window->draw(backgroundSP);
	window->draw(playerSP);
	window->draw(player2SP);

	window->display();
}
