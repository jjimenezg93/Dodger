#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)


#include "../include/u-gine.h"

#include "conio.h"
#include <iostream>
#include <string>
#include <ctime>

#define DIFFICULTY 3
#define POINT_RATE 10
#define BORDER_THRESHOLD 5

//DG = DODGER
enum Color { DG_CLR_RED, DG_CLR_GREEN, DG_CLR_BLUE, DG_CLR_YELLOW, DG_CLR_WHITE, DG_CLR_NUM_COLORS };

int speed = 256;

struct Rect {
public:
	Rect(float x, float y, float sX, float sY, short int dX, short int dY, Color c) {
		this->x = x;
		this->y = y;
		if (dX == 0)
			this->speedX = speed;
		else
			this->speedX = speed * dX;
		if (dY == 0)
			this->speedY = speed;
		else
			this->speedY = speed * dY;
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

float genRandomF(double min, double max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min) + min);
}

void checkAndUpdateSpriteDirection(Rect *enemy) {
	if (enemy->getX() >= Screen::Instance().GetWidth() - enemy->getSizeX() - BORDER_THRESHOLD || enemy->getX() <= BORDER_THRESHOLD)
		enemy->setSpeedX(enemy->getSpeedX() * -1);
	if (enemy->getY() >= Screen::Instance().GetHeight() - enemy->getSizeY() - BORDER_THRESHOLD || enemy->getY() <= BORDER_THRESHOLD)
		enemy->setSpeedY(enemy->getSpeedY() * -1);
}

Color RandColort()
{
	Color c = (Color)(unsigned)(rand() % DG_CLR_NUM_COLORS);
	if (c == DG_CLR_WHITE)
		c = DG_CLR_RED;
	return c;
}

void setPaintingColor(Rect *rect) {
	switch (rect->getColor()) {
	case DG_CLR_RED:
		Renderer::Instance().SetColor(255, 0, 0, 255);
		break;
	case DG_CLR_GREEN:
		Renderer::Instance().SetColor(0, 255, 0, 255);
		break;
	case DG_CLR_BLUE:
		Renderer::Instance().SetColor(0, 0, 255, 255);
		break;
	case DG_CLR_YELLOW:
		Renderer::Instance().SetColor(255, 255, 0, 255);
		break;
	case DG_CLR_WHITE:
		Renderer::Instance().SetColor(255, 255, 255, 255);
		break;
	}

}

bool isCollision(Rect *ra, Rect *rb) {
	bool ret = false;
	if (ra->getX() >= rb->getX() && ra->getX() <= rb->getX() + rb->getSizeX()
		&& ra->getY() >= rb->getY() && ra->getY() <= rb->getY() + rb->getSizeY())
		//finish game
		ret = true;

	if (ra->getX() + ra->getSizeX() >= rb->getX() && ra->getX() + ra->getSizeX() <= rb->getX() + rb->getSizeX()
		&& ra->getY() + ra->getSizeY() >= rb->getY() && ra->getY() + ra->getSizeY() <= rb->getY() + rb->getSizeY())
		//finish game
		ret = true;

	return ret;
}

//memory must be deallocated
Rect * randomSpawnEnemy() {
	Rect *enemy = new Rect(genRandomF(200, Screen::Instance().GetWidth() - 200), genRandomF(200, Screen::Instance().GetHeight() - 200)
		, genRandomF(20, 100), genRandomF(20, 100), genRandomF(-1, 1), genRandomF(-1, 1), RandColort());
	enemy->setSpeedX(genRandomF(0.2 * DIFFICULTY, 0.8 * DIFFICULTY));
	enemy->setSpeedY(genRandomF(0.2 * DIFFICULTY, 0.8 * DIFFICULTY));
	return enemy;
}

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	unsigned short int key = 0;

	bool flagGame = true;

	Rect *pj = new Rect(0, 0, 16, 16, 0, 0, DG_CLR_WHITE);
	pj->setSpeedX(speed);
	pj->setSpeedY(speed);

	Array<Rect *> enemies;

	unsigned short int points = 0;

	String title = String("Points = ");

	for (unsigned short int i = 0; i < DIFFICULTY; i++) {
		enemies.Add(randomSpawnEnemy());
	}

	int f = 0;

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC) && flagGame == true) {
		Renderer::Instance().Clear();

		Screen::Instance().SetTitle(title + String::FromInt(points) + " | Speed = " + String::FromInt(speed));

		/* WHITE BACKGROUND
		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawRect(0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());*/

		setPaintingColor(pj);

		f = genRandomF(0, 7000);

		if (f % 150 == 0)
			enemies.Add(randomSpawnEnemy());

		if (!f)
			enemies.RemoveAt(f);

		//input
		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT) && pj->getX() > 0)
			pj->setX(pj->getX() - pj->getSpeedX() * Screen::Instance().ElapsedTime());
		else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT) && pj->getX() < Screen::Instance().GetWidth() - pj->getSizeX())
			pj->setX(pj->getX() + pj->getSpeedX() * Screen::Instance().ElapsedTime());
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP) && pj->getY() > 0)
			pj->setY(pj->getY() - pj->getSpeedY() * Screen::Instance().ElapsedTime());
		else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN) && pj->getY() < Screen::Instance().GetHeight() - pj->getSizeY())
			pj->setY(pj->getY() + pj->getSpeedY() * Screen::Instance().ElapsedTime());

		//player render
		Renderer::Instance().DrawRect(pj->getX(), pj->getY(), pj->getSizeX(), pj->getSizeY());

		//collision
		for (unsigned short int i = 0; i < enemies.Size(); i++) {
			if (isCollision(pj, enemies[i]) && enemies[i]->getColor() == DG_CLR_RED)
				flagGame = false;
			if (isCollision(pj, enemies[i]) && enemies[i]->getColor() == DG_CLR_GREEN) {
				points += POINT_RATE;
				delete enemies[i];
				enemies.RemoveAt(i);
			}
			if (isCollision(pj, enemies[i]) && enemies[i]->getColor() == DG_CLR_BLUE) {
				speed -= 32;
				delete enemies[i];
				enemies.RemoveAt(i);
			}
			if (isCollision(pj, enemies[i]) && enemies[i]->getColor() == DG_CLR_YELLOW) {
				speed += 32;
				delete enemies[i];
				enemies.RemoveAt(i);
			}
		}

		for (unsigned short int i = 0; i < enemies.Size(); i++) {
			Renderer::Instance().SetColor(255, 0, 0, 255);
			
			//update
			enemies[i]->setX(enemies[i]->getX() + (enemies[i]->getSpeedX() * speed) * Screen::Instance().ElapsedTime());
			enemies[i]->setY(enemies[i]->getY() + (enemies[i]->getSpeedY() * speed) * Screen::Instance().ElapsedTime());
			
			//check direction
			checkAndUpdateSpriteDirection(enemies[i]);

			//render
			setPaintingColor(enemies[i]);
			Renderer::Instance().DrawRect(enemies[i]->getX(), enemies[i]->getY(), enemies[i]->getSizeX(), enemies[i]->getSizeY());
		}

		Screen::Instance().Refresh();
	}

	for (unsigned short int i = 0; i < enemies.Size(); i++)
		delete enemies[i];

	delete pj;

	return 0;
}
