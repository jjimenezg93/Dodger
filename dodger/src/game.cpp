#include <ctime>
#include <stdio.h>

#include "../include/as_start_menu.h"
#include "../include/defs.h"
#include "../include/entity.h"
#include "../include/game.h"
#include "../include/ui.h"
#include "../include/world.h"

//default World params
#define DEFAULT_WORLD_ID 0
#define DEFAULT_MAX_COLLIDABLES 4
#define DEFAULT_INIT_SPEED 256

Game::~Game() {
	delete m_ui;
	delete m_world;
}

void Game::Init() {
	srand(static_cast<unsigned int>(time(nullptr)));

	m_points = 0;

	String * fileName = nullptr;

	if (g_currentMenuOp == EDMO_LEVEL_1)
		fileName = new String(LEVEL_1_FILENAME);
	else if (g_currentMenuOp == EDMO_LEVEL_2)
		fileName = new String(LEVEL_2_FILENAME);
	else if (g_currentMenuOp == EDMO_LEVEL_3)
		fileName = new String(LEVEL_3_FILENAME);

	if (fileName) {
		Array<String> arrayParams;
		ReadFile(fileName, arrayParams);

		m_world = new World(arrayParams[0], arrayParams[1].ToInt(),
			arrayParams[2].ToInt(), arrayParams[3].ToInt());
		m_ui = new UI(m_world);
	} else {
		//default world params
		unsigned short int worldId = DEFAULT_WORLD_ID;
		unsigned short int maxCollidables = DEFAULT_MAX_COLLIDABLES;
		unsigned short int initialSpeed = DEFAULT_INIT_SPEED;
	
		m_world = new World(DEFAULT_BACKGROUND, worldId, maxCollidables, initialSpeed);
		m_ui = new UI(m_world);
	}

	m_windowTitle = String("Points = ");

	delete fileName;
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
	Screen::Instance().SetTitle(m_windowTitle + String::FromInt(m_points)
		+ " | Speed = " + String::FromInt(m_speed));

	m_world->Draw();
}

int Game::GetWorldSpeed() const {
	return m_world->GetWorldSpeed();
}

//param order: bg_file, id, max_collidables, init_speed
void Game::ReadFile(const String *fileName, Array<String> &paramsArray) {
	String strFile = String::Read(*fileName);
	paramsArray = strFile.Split(String(","));
}
