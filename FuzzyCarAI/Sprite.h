#pragma once
#include "SFML\Graphics.hpp"
class Sprite : public sf::RectangleShape
{
public:
	Sprite(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Sprite();

	virtual void update(float dt) = 0;

	// Set velocity of the sprite.
	void setVelocity(float vx, float vy);

	// Get velocity of the sprite.
	sf::Vector2f getVelocity();

protected:
	sf::Vector2f velocity;	// The velocity vector for this object.
};