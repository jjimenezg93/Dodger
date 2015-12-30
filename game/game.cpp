#include <ctime>
#include <stdio.h>

#include "as_start_menu.h"
#include "defs.h"
#include "game.h"
#include "entity.h"
#include "ui.h"
#include "world.h"

Game::~Game() {
	delete m_ui;
	delete m_world;
	Screen::Instance().SetTitle(String("DODGER"));
}

void Game::Init() {
	srand(time(nullptr));

	m_points = 0;

	//from file
	String *fileName;

	if (currentMenuOp == EM_LEVEL_1) {
		fileName = new String(LEVEL_1_FILENAME);
	} else if (currentMenuOp == EM_LEVEL_2) {
		fileName = new String(LEVEL_2_FILENAME);
	} else if (currentMenuOp == EM_LEVEL_3) {
		fileName = new String(LEVEL_3_FILENAME);
	}

	if (fileName) {
		Array<String> arrayParams;

		ReadFile(fileName, arrayParams);

		m_world = new World(arrayParams[0], arrayParams[1].ToInt(), arrayParams[2].ToInt(), arrayParams[3].ToInt());
		m_ui = new UI(m_world);
	} else {
		unsigned short int worldId = 0;
		unsigned short int maxEnemies = 4;
		unsigned short int initialSpeed = 256;
	
		m_world = new World(DEFAULT_BACKGROUND, worldId, maxEnemies, initialSpeed);
		m_ui = new UI(m_world);
	}

	delete fileName;

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
//id, max_enemies, init_speed
void Game::ReadFile(const String *fileName, Array<String> &paramsArray) {
	String strFile = String::Read(*fileName);
	paramsArray = strFile.Split(String(","));
}
