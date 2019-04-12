#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

// Input setter functions.
void Input::setKeyDown(int key)
{
	keys[key] = true;
}
void Input::setKeyUp(int key)
{
	keys[key] = false;
}

// Input getter functions.
bool Input::isKeyDown(int key)
{
	return keys[key];
}