#include "as_menu.h"
#include "as_game.h"
#include "defs.h"
#include "../include/u-gine.h"

void ASMenu::Activate() {
}

void ASMenu::ProcessInput() {
	if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
		g_wantedState = new ASGame();
	} else if (Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		g_wantedState = nullptr;
	}
}

void ASMenu::Run() {
}

void ASMenu::Draw() {
	Renderer::Instance().Clear();

	Renderer::Instance().SetColor(255, 255, 255, 255);

	Renderer::Instance().DrawRect(0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());

	Screen::Instance().Refresh();
}

void ASMenu::Deactivate() {
}
