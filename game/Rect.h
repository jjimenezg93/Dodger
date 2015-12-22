#ifndef RECT_H
#define RECT_H

#include "game.h"
#include "defs.h"

class Rect {
public:
	Rect(float x, float y, float sX, float sY, short int dX, short int dY, Color c) {
		this->x = x;
		this->y = y;
		if (dX == 0)
			this->speedX = g_game->GetGameSpeed();
		else
			this->speedX = g_game->GetGameSpeed() * dX;
		if (dY == 0)
			this->speedY = g_game->GetGameSpeed();
		else
			this->speedY = g_game->GetGameSpeed() * dY;
		this->sizeX = sX;
		this->sizeY = sY;
		this->color = c;
	}

	float getX() { return this->x; }
	float getY() { return this->y; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }

	float getSizeX() { return this->sizeX; }
	float getSizeY() { return this->sizeY; }
	void setSizeX(float x) { this->sizeX = x; }
	void setSizeY(float y) { this->sizeY = y; }

	float getSpeedX() { return this->speedX; }
	float getSpeedY() { return this->speedY; }
	void setSpeedX(float x) { this->speedX = x; }
	void setSpeedY(float y) { this->speedY = y; }

	Color getColor() { return this->color; };
	void setColor(Color c) { this->color = c; };
private:
	float x, y;
	float sizeX, sizeY;
	float speedX, speedY;
	Color color;
};

#endif