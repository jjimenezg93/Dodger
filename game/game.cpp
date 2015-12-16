#include <ctime>

#include "Rect.h"
#include "as_menu.h"
#include "defs.h"
#include "game.h"

#define DIFFICULTY 3
#define POINT_RATE 10
#define BORDER_THRESHOLD 10
#define MIN_OBJECT_SIZE 20
#define MAX_OBJECT_SIZE 100
#define SPAWN_BORDER 200
#define DIRECTION_LEFT -1
#define DIRECTION_RIGHT 1

float genRandomF(double min, double max);
Color RandColort();
void setPaintingColor(Rect *rect);

void Game::Init() {
	srand(time(nullptr));
	
	this->m_speed = 256;

	this->m_player = new Rect(0, 0, 16, 16, 0, 0, DG_CLR_WHITE);
	m_player->setSpeedX(this->m_speed);
	m_player->setSpeedY(this->m_speed);

	this->m_points = 0;

	for (unsigned short int i = 0; i < 4; i++) {
		this->m_objects.Add(this->randomSpawnObject());
	}
	
	this->m_windowTitle = String("Points = ");
}

void Game::ProcessInput() {
	if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		g_wantedState = nullptr;
	}

	if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT) && m_player->getX() > 0)
		m_player->setX(m_player->getX() - m_player->getSpeedX() * Screen::Instance().ElapsedTime());
	else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT) && m_player->getX() < Screen::Instance().GetWidth() - m_player->getSizeX())
		m_player->setX(m_player->getX() + m_player->getSpeedX() * Screen::Instance().ElapsedTime());
	if (Screen::Instance().KeyPressed(GLFW_KEY_UP) && m_player->getY() > 0)
		m_player->setY(m_player->getY() - m_player->getSpeedY() * Screen::Instance().ElapsedTime());
	else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN) && m_player->getY() < Screen::Instance().GetHeight() - m_player->getSizeY())
		m_player->setY(m_player->getY() + m_player->getSpeedY() * Screen::Instance().ElapsedTime());
}

void Game::Run() {

	this->m_randomGen = genRandomF(0, 7000);

	if (this->m_randomGen % 150 == 0)
		this->m_objects.Add(this->randomSpawnObject());

	if (!this->m_randomGen) {
		delete this->m_objects[this->m_randomGen];
		this->m_objects.RemoveAt(this->m_randomGen);
	}

	for (unsigned short int i = 0; i < this->m_objects.Size(); i++) {
		if (isCollision(this->m_player, this->m_objects[i]) && this->m_objects[i]->getColor() == DG_CLR_RED)
			g_wantedState = new ASMenu();
		if (isCollision(this->m_player, this->m_objects[i]) && this->m_objects[i]->getColor() == DG_CLR_GREEN) {
			this->m_points += POINT_RATE;
			this->despawnObject(i);
		}
		if (isCollision(this->m_player, this->m_objects[i]) && this->m_objects[i]->getColor() == DG_CLR_BLUE) {
			this->m_speed -= 32;
			this->despawnObject(i);
		}
		if (isCollision(this->m_player, this->m_objects[i]) && this->m_objects[i]->getColor() == DG_CLR_YELLOW) {
			this->m_speed += 32;
			this->despawnObject(i);
		}

		//check direction
		checkAndUpdateObjectDirection(this->m_objects[i]);

		//update position
		this->m_objects[i]->setX(this->m_objects[i]->getX() + (this->m_objects[i]->getSpeedX() * this->m_speed) * Screen::Instance().ElapsedTime());
		this->m_objects[i]->setY(this->m_objects[i]->getY() + (this->m_objects[i]->getSpeedY() * this->m_speed) * Screen::Instance().ElapsedTime());
	}

}

void Game::Draw() {
	Renderer::Instance().Clear();

	Screen::Instance().SetTitle(this->m_windowTitle + String::FromInt(this->m_points) + " | Speed = " + String::FromInt(this->m_speed));

	//player rendering
	setPaintingColor(this->m_player);
	Renderer::Instance().DrawRect(this->m_player->getX(), this->m_player->getY(), this->m_player->getSizeX(), this->m_player->getSizeY());

	//objects rendering
	for (unsigned short int i = 0; i < this->m_objects.Size(); i++) {
		Renderer::Instance().SetColor(255, 0, 0, 255);

		setPaintingColor(this->m_objects[i]);
		Renderer::Instance().DrawRect(this->m_objects[i]->getX(), this->m_objects[i]->getY(), this->m_objects[i]->getSizeX(), this->m_objects[i]->getSizeY());
	}

	Screen::Instance().Refresh();
}

bool Game::isCollision(Rect *ra, Rect *rb) {
	bool ret = false;
	if (ra->getX() >= rb->getX() && ra->getX() <= rb->getX() + rb->getSizeX()
		&& ra->getY() >= rb->getY() && ra->getY() <= rb->getY() + rb->getSizeY())
		ret = true;

	if (ra->getX() + ra->getSizeX() >= rb->getX() && ra->getX() + ra->getSizeX() <= rb->getX() + rb->getSizeX()
		&& ra->getY() + ra->getSizeY() >= rb->getY() && ra->getY() + ra->getSizeY() <= rb->getY() + rb->getSizeY())
		ret = true;

	return ret;
}

Rect * Game::randomSpawnObject() {
	Rect *enemy = new Rect(genRandomF(SPAWN_BORDER, Screen::Instance().GetWidth() - SPAWN_BORDER), genRandomF(SPAWN_BORDER, Screen::Instance().GetHeight() - SPAWN_BORDER)
		, genRandomF(MIN_OBJECT_SIZE, MAX_OBJECT_SIZE), genRandomF(MIN_OBJECT_SIZE, MAX_OBJECT_SIZE), genRandomF(DIRECTION_LEFT, DIRECTION_RIGHT), genRandomF(DIRECTION_LEFT, DIRECTION_RIGHT), RandColort());
	enemy->setSpeedX(genRandomF(0.2 * DIFFICULTY, 0.8 * DIFFICULTY));
	enemy->setSpeedY(genRandomF(0.2 * DIFFICULTY, 0.8 * DIFFICULTY));
	return enemy;
}

void Game::despawnObject(int pos) {
	delete this->m_objects[pos];
	this->m_objects.RemoveAt(pos);
}

void Game::checkAndUpdateObjectDirection(Rect *object) {
	if (object->getX() >= Screen::Instance().GetWidth() - object->getSizeX() - BORDER_THRESHOLD || object->getX() <= BORDER_THRESHOLD)
		object->setSpeedX(object->getSpeedX() * -1);
	if (object->getY() >= Screen::Instance().GetHeight() - object->getSizeY() - BORDER_THRESHOLD || object->getY() <= BORDER_THRESHOLD)
		object->setSpeedY(object->getSpeedY() * -1);
}

float genRandomF(double min, double max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min) + min);
}

Color RandColort() {
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