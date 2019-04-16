
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
	playerSP.setSize(sf::Vector2f(100, 200));
	playerSP.setTexture(&playerTX);
	playerSP.setOrigin(50, 100);
	playerSP.setVelocity(-1.0f, 0.0f);

	// Player 2 sprite
	if (!player2TX.loadFromFile("graphics/player2.png"))
	{
		// error
	}
	player2SP.setSize(sf::Vector2f(100, 200));
	player2SP.setTexture(&player2TX);
	player2SP.setOrigin(50, 100);
	//player2SP.setVelocity(1.0f, 0.0f);

	playerSP.setPosition(166, 100);	
	player2SP.setPosition(632, 500);

	// Line sprite
	if (!lineTX.loadFromFile("graphics/line.png"))
	{
		// error
	}
	lineSP.setTexture(&lineTX);
	lineSP.setSize(sf::Vector2f(10, 600));
	lineSP.setPosition(398.0f, 000.0f);
}

Game::~Game()
{

}

void Game::update(float* delta)
{
	// MOVE RACING LINE
	if (input->isKeyDown(sf::Keyboard::A)) {
		racingLineXVal -= 0.5f;
	}
	else if (input->isKeyDown(sf::Keyboard::D)) {
		racingLineXVal += 0.5f;
	}
	// CLAMP RACING LINE
	if (racingLineXVal > 796) {
		racingLineXVal = 796;
	}
	else if (racingLineXVal < 0) {
		racingLineXVal = 0;
	}
	// SET RACING LINE SPRITE POSITION
	lineSP.setPosition(racingLineXVal, 0.0f);
	// COMPUTE DISTANCES FROM LINE
	float player1Dis = (playerSP.getPosition().x - racingLineXVal) / 400;
	float player2Dis = (player2SP.getPosition().x - racingLineXVal) / 400;
	// SETUP INPUT AND OUTPUT VARIABLES
	fl::InputVariable* distance = engine->getInputVariable("Distance");
	fl::InputVariable* velocity = engine->getInputVariable("Velocity");
	fl::OutputVariable* steering = engine->getOutputVariable("Steering");
	// PROCESS PLAYER ONE (FUZZY)
	distance->setValue(player1Dis);
	velocity->setValue(playerSP.getVelocity().x);

	engine->process();

	playerSP.setVelocity(steering->getValue(), 0.0f);
	playerSP.setPosition(playerSP.getPosition() + playerSP.getVelocity());
	playerSP.update(*delta);

	// PROCESS PLAYER TWO (DIFFERENT METHOD)

	player2SP.setPosition(player2SP.getPosition() + player2SP.getVelocity());
	player2SP.update(*delta);

	// Testing 
	//cout << std::to_string(velocity->getValue()); // switch to steering, velocity or distance to test
	//cout << endl;

	render();
}

void Game::render()
{
	window->clear(sf::Color::White);

	window->draw(backgroundSP);
	window->draw(playerSP);
	window->draw(player2SP);
	window->draw(lineSP);

	window->display();
}
