#include "../include/defs.h"
#include "../include/ui.h"
#include "../../include/u-gine.h"
#include "../include/world.h"

UI::UI(World *ptrWorld) {
	m_world = ptrWorld;
}

void UI::ProcessInput() {
	if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		GSetWantedState(EAS_GAME_OVER);
		g_currentMenuOp = EMO_GAME_OVER;
	}

	if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT))
		m_world->MoveLeft();
	else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT))
		m_world->MoveRight();
	if (Screen::Instance().KeyPressed(GLFW_KEY_UP))
		m_world->MoveUp();
	else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN))
		m_world->MoveDown();
}

void UI::Draw() {
}

void UI::SetWorld(World *ptrWorld) {
	m_world = ptrWorld;
}