#include "../include/player.h"

Player::Player(double x, double y, short int dirX, short int dirY)
	: Entity(x, y, dirX, dirY, EDET_PLAYER) {
}

/*void Player::MoveLeft(double elapsed) {
	if (GetX() > 0)
		SetX(GetX() - GetSpeedX() * elapsed);
	if (GetX() < 0)
		SetX(0);
}

void Player::MoveRight(double elapsed) {
	if (GetX() < Screen::Instance().GetWidth() - GetSizeX())
		SetX(GetX() + GetSpeedX() * elapsed);
	if (GetX() > Screen::Instance().GetWidth() - GetSizeX())
		SetX(Screen::Instance().GetWidth() - GetSizeX());
}

void Player::MoveUp(double elapsed) {
	if (GetY() > 0)
		SetY(GetY() - GetSpeedY() * elapsed);
	if (GetY() < 0)
		SetY(0);
}

void Player::MoveDown(double elapsed) {
	if (GetY() < Screen::Instance().GetHeight() - GetSizeY())
		SetY(GetY() + GetSpeedY() * elapsed);
	if (GetY() > Screen::Instance().GetHeight() - GetSizeY())
		SetY(Screen::Instance().GetHeight() - GetSizeY());
}*/