#include "player.h"

Player::Player(Image * imgSprite, double x, double y, short int dirX, short int dirY)
	: Entity(imgSprite, x, y, dirX, dirY, ET_PLAYER) {
}

void Player::MoveLeft(double elapsed) {
	if (GetX() > 0)
		SetX(GetX() - m_speedX * elapsed);
	if (GetX() < 0)
		SetX(0);
}

void Player::MoveRight(double elapsed) {
	if (GetX() < Screen::Instance().GetWidth() - m_sizeX)
		SetX(GetX() + m_speedX * elapsed);
	if (GetX() > Screen::Instance().GetWidth() - m_sizeX)
		SetX(Screen::Instance().GetWidth() - m_sizeX);
}

void Player::MoveUp(double elapsed) {
	if (GetY() > 0)
		SetY(GetY() - m_speedY * elapsed);
	if (GetY() < 0)
		SetY(0);
}

void Player::MoveDown(double elapsed) {
	if (GetY() < Screen::Instance().GetHeight() - m_sizeY)
		SetY(GetY() + m_speedY * elapsed);
	if (GetY() > Screen::Instance().GetHeight() - m_sizeY)
		SetY(Screen::Instance().GetHeight() - m_sizeY);
}