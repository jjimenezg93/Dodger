#include "../include/component_playercontrol.h"
#include "../include/defs.h"
#include "../include/ui.h"
#include "../include/messages.h"
#include "../../include/u-gine.h"
#include "../include/world.h"
#include "../include/player.h"


UI::UI(World *ptrWorld) {
	m_world = ptrWorld;
}

void UI::ProcessInput() {
	if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		GSetWantedState(EDAS_GAME_OVER);
		g_currentMenuOp = EDMO_GAME_OVER;
	}

	if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT))
		m_world->GetPlayer()->ReceiveMessage(new PlayerControlMessage(EDPC_LEFT));
	else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT))
		m_world->GetPlayer()->ReceiveMessage(new PlayerControlMessage(EDPC_RIGHT));
	if (Screen::Instance().KeyPressed(GLFW_KEY_UP))
		m_world->GetPlayer()->ReceiveMessage(new PlayerControlMessage(EDPC_UP));
	else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN))
		m_world->GetPlayer()->ReceiveMessage(new PlayerControlMessage(EDPC_DOWN));
}

void UI::Draw() {}

void UI::SetWorld(World *ptrWorld) {
	m_world = ptrWorld;
}