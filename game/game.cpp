#include <ctime>

#include "as_start_menu.h"
#include "defs.h"
#include "game.h"
#include "entity.h"
#include "ui.h"
#include "world.h"

Game::~Game() {
	delete m_ui;
	delete m_world;
}

void Game::Init() {
	srand(time(nullptr));
	
	m_points = 0;

	//from file
	unsigned short int worldId = 0;
	unsigned short int maxEnemies = 4;
	unsigned short int initialSpeed = 256;

	m_world = new World(worldId, maxEnemies, initialSpeed);
	m_ui = new UI(m_world);
	
	m_windowTitle = String("Points = ");
}

void Game::ProcessInput() {
	m_ui->ProcessInput();
}

void Game::Run() {
	m_randomGen = rand();
	m_world->Run();
	m_speed = m_world->GetWorldSpeed();
}

void Game::Draw() {
	Screen::Instance().SetTitle(m_windowTitle + String::FromInt(m_points) + " | Speed = " + String::FromInt(m_speed));
	m_world->Draw();
}

World * Game::GetWorld() const {
	return m_world;
}

int Game::GetWorldSpeed() const {
	return m_world->GetWorldSpeed();
}

int Game::GetPoints() const {
	return m_points;
}

void Game::AddPoints(int p) {
	m_points += p;
}

void Game::SubtractPoints(int p) {
	m_points -= p;
}