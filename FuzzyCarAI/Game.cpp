#include "Game.h"
#include "fl/Headers.h"

#include <iostream>
#include <fstream>

using namespace std;

// Player 2 state
enum Player2State { HardLeft, Left, Centre, Right, HardRight };
Player2State PoliceState;

// Timer for fuzzy logic
sf::Clock fuzzyClock;
// Timer for FSM logic
sf::Clock finiteClock;
// AI-tick
#define AITick 0.25f

// Testing file
// define the ofstream file
ofstream fuzzyFile;
ofstream finiteFile;

Game::Game(sf::RenderWindow* hwnd, Input* in, fl::Engine* engi)
{
	std::string fuzzyFilename; // Fuzzy test data
	fuzzyFilename = "fuzzyTestData.csv";
	fuzzyFile.open(fuzzyFilename);
	fuzzyFile << "DISTANCE" << "," << "VELOCITY" << "," << "STEERING" << endl;

	std::string finiteFilename; // FSM test data
	finiteFilename = "finiteTestData.csv";
	finiteFile.open(finiteFilename);
	finiteFile << "DISTANCE" << "," << "VELOCITY" << "," << "STEERING" << endl;


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


	// Player 2 sprite
	if (!player2TX.loadFromFile("graphics/player2.png"))
	{
		// error
	}
	player2SP.setSize(sf::Vector2f(100, 200));
	player2SP.setTexture(&player2TX);
	player2SP.setOrigin(50, 100);


	// Set initial player positions
	playerSP.setPosition(166, 150);	
	player2SP.setPosition(632, 450);


	// Line sprite
	if (!lineTX.loadFromFile("graphics/line.png"))
	{
		// error
	}
	lineSP.setTexture(&lineTX);
	lineSP.setSize(sf::Vector2f(10, 600));
	lineSP.setPosition(398.0f, 000.0f);


	// Calculate window length
	windowLength = window->getSize().x / 2;
}

Game::~Game()
{

}

void Game::update(float* delta)
{
	// Handle racing line input
	HandleInput();
	// Clamp racing line within screen
	Clamp();
	// Set racing line position
	lineSP.setPosition(racingLineXVal, 0.0f);


	// Compute distance from line for both cars
	float player1Dis = (playerSP.getPosition().x - racingLineXVal) / windowLength;
	float player2Dis = (player2SP.getPosition().x - racingLineXVal) / windowLength;


	// Get time elapsed since last fuzzy check
	float fuzzyElapsed = fuzzyClock.getElapsedTime().asSeconds();
	if (fuzzyElapsed > AITick) {
		// Setup fuzzylite input and output variables
		fl::InputVariable* distance = engine->getInputVariable("Distance");
		fl::InputVariable* velocity = engine->getInputVariable("Velocity");
		fl::OutputVariable* steering = engine->getOutputVariable("Steering");
		// Assign values in fuzzy control system 
		distance->setValue(player1Dis);
		velocity->setValue(playerSP.getVelocity().x);
		// Process the fuzzy logic
		engine->process();
		// Set velocity
		player1Vel = steering->getValue();
		// Reset timer
		fuzzyClock.restart();
		// Output test data
		fuzzyFile << player1Dis << "," << player1Vel << "," << steering->getValue() << endl;
	}

	// Update player one
	playerSP.setVelocity(player1Vel, 0.0f);
	playerSP.setPosition(playerSP.getPosition() + playerSP.getVelocity()*1.0f);
	playerSP.setRotation(player1Dis * -22.5f);
	playerSP.update(*delta);
	

	// Get time elapsed since last fuzzy check
	float finiteElapsed = finiteClock.getElapsedTime().asSeconds();
	if (finiteElapsed > AITick) {
		// Process player two finite state machine
		stateUpdate(player2Dis);
		// Check player two state and update velocity
		checkState();
		// Reset timer
		finiteClock.restart();
		// Test data
		finiteFile << player2Dis << "," << player2Vel << "," << PoliceState << endl;
	}

	// Update player two
	player2SP.setVelocity(player2Vel, 0.0f);
	player2SP.setPosition(player2SP.getPosition() + player2SP.getVelocity()*1.0f);
	player2SP.setRotation(player2Dis * -22.5f);
	player2SP.update(*delta);


	// Render game
	render();
}

void Game::checkState()
{
	switch (PoliceState) {
	case HardLeft:
		player2Vel = -0.4f;
		break;
	case Left:
		player2Vel = -0.175f;
		break;
	case Centre:
		player2Vel = 0.0f;
		break;
	case Right:
		player2Vel = 0.175f;
		break;
	case HardRight:
		player2Vel = 0.4f;
		break;
	}
}

void Game::HandleInput()
{
	if (input->isKeyDown(sf::Keyboard::A)) {
		racingLineXVal -= 0.5f;
	}
	else if (input->isKeyDown(sf::Keyboard::D)) {
		racingLineXVal += 0.5f;
	}
}

void Game::Clamp()
{
	if (racingLineXVal > 790) {
		racingLineXVal = 790;
	}
	else if (racingLineXVal < 0) {
		racingLineXVal = 0;
	}
}

void Game::render()
{
	window->clear(sf::Color::White);

	window->draw(backgroundSP);
	window->draw(lineSP);
	window->draw(playerSP);
	window->draw(player2SP);

	window->display();
}

void Game::stateUpdate(float dis)
{
	if (dis > 0.05) {
		if (dis > 0.8) {
			PoliceState = HardLeft;
		} 
		if (dis > 0 && dis <= 0.8) {
			PoliceState = Left;
		}
	}
	else if (dis < -0.05) {
		if (dis < -0.8) {
			PoliceState = HardRight;
		}
		if (dis < 0 && dis >= -0.8) {
			PoliceState = Right;
		}
	}
	else {
		PoliceState = Centre;
	}
}
