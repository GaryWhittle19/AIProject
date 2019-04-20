#pragma once

class Input
{
public:
	Input();
	~Input();

	// Input setters
	void setKeyDown(int key);
	void setKeyUp(int key);
	// Is key down?
	bool isKeyDown(int key);

protected:
	bool keys[256]{ false };
};