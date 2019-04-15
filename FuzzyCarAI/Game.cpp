
/** GAME HEADER */
#include "Game.h"
#include "fl/Headers.h"

#include <iostream>

using namespace std;

Game::Game(sf::RenderWindow* hwnd, Input* in, fl::Engine* engi)
{
	// Setup access to SFML window and Input class
	window = hwnd;
	input = in;
	engine = engi;

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
	playerSP.setVelocity(-1.0f, 0.0f);

	// Player 2 sprite
	if (!player2TX.loadFromFile("graphics/player2.png"))
	{
		// error
	}
	player2SP.setSize(sf::Vector2f(160, 120));
	player2SP.setTexture(&player2TX);
	player2SP.setOrigin(80, 60);
	player2SP.setVelocity(1.0f, 0.0f);

	playerSP.setPosition(266, 100);	
	player2SP.setPosition(532, 500);
}

Game::~Game()
{

}

void Game::update(float* delta)
{
	float player1Dis;
	if (playerSP.getPosition().x < 400) {
		player1Dis = playerSP.getPosition().x / 400 * -1;
	}
	else if (playerSP.getPosition().x > 400) {
		player1Dis = (playerSP.getPosition().x - 400) / 400;
	}
	
	float player2Dis;
	if (player2SP.getPosition().x < 400) {
		player2Dis = player2SP.getPosition().x / 400 * -1;
	}
	else if (player2SP.getPosition().x > 400) {
		player2Dis = (player2SP.getPosition().x - 400) / 400;
	}

	fl::InputVariable* distance = engine->getInputVariable("Distance");
	fl::InputVariable* velocity = engine->getInputVariable("Velocity");
	fl::OutputVariable* steering = engine->getOutputVariable("Steering");

	// Process player one
	distance->setValue(player1Dis);
	velocity->setValue(playerSP.getVelocity().x);

	engine->process();

	playerSP.setVelocity(steering->getValue(), 0.0f);
	playerSP.setPosition(playerSP.getPosition() + playerSP.getVelocity());
	playerSP.update(*delta);

	// Process player two
	distance->setValue(player2Dis);
	velocity->setValue(player2SP.getVelocity().x);

	engine->process();

	player2SP.setVelocity(steering->getValue(), 0.0f);
	player2SP.setPosition(player2SP.getPosition() + player2SP.getVelocity());
	player2SP.update(*delta);

	// Testing 

	cout << std::to_string(velocity->getValue()); // switch to steering, velocity or distance to test
	cout << endl;

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
