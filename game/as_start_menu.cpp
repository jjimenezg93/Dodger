#include "as_start_menu.h"
#include "as_game.h"
#include "defs.h"
#include "../include/u-gine.h"

#define MENU_MARGIN 150
#define MENU_POINTER_MARGIN 32
#define MENU_POINTER_SIZE 4

void ASStartMenu::Activate() {
	m_mainFont = ResourceManager::Instance().LoadFont("data/monospaced.png");

	m_menuOptions.Add(new MenuOption(EM_START_GAME, new String("Enter - Start Game")));
	m_menuOptions.Add(new MenuOption(EM_EXIT_APP, new String("ESC - Exit Game")));

	m_imgBackground = new Image(SPACE_BACKGROUND);

	m_activeOption = 0;
}

void ASStartMenu::Deactivate() {
	for (uint8 i = 0; i < m_menuOptions.Size(); i++) {
		delete m_menuOptions[i];
	}

	//more effective way of holding font?
	ResourceManager::Instance().FreeFonts();
}

void ASStartMenu::ProcessInput() {
	if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
		if (m_menuOptions[m_activeOption]->option == EM_START_GAME)
			GSetWantedState(AS_GAME);
		else if (m_menuOptions[m_activeOption]->option == EM_EXIT_APP)
			GSetWantedState(AS_EXIT_APP);
	}

	if (Screen::Instance().KeyPressed(GLFW_KEY_UP) && m_activeOption > 0)
		m_activeOption--;
	else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN) && m_activeOption < m_menuOptions.Size() - 1)
		m_activeOption++;
}

void ASStartMenu::Run() {

}

void ASStartMenu::Draw() {
	Renderer::Instance().Clear();

	//background
	if (m_imgBackground) {
		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawImage(m_imgBackground, 0, 0);
	} else {
		Renderer::Instance().SetColor(0, 0, 0, 255);
		Renderer::Instance().DrawRect(0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight());
	}

	//start game text
	for (uint8 i = 0; i < m_menuOptions.Size(); i++) {
		m_mainFont->SetX(Screen::Instance().GetWidth() / 2 - (m_mainFont->GetTextWidth(*m_menuOptions[i]->text) / 2));
		m_mainFont->SetY(MENU_MARGIN + (Screen::Instance().GetHeight() / m_mainFont->GetTextHeight(*m_menuOptions[i]->text) * i));
		
		if (i == m_activeOption) {
			Renderer::Instance().SetColor(0, 255, 0, 255);
			Renderer::Instance().DrawEllipse(m_mainFont->GetX() - MENU_POINTER_MARGIN, m_mainFont->GetY() + m_mainFont->GetTextHeight(*m_menuOptions[i]->text) / 2, 4, 4);
		} else
			Renderer::Instance().SetColor(0, 0, 255, 255);
		m_mainFont->Render(*m_menuOptions[i]->text, m_mainFont->GetX(), m_mainFont->GetY());
	}

	Screen::Instance().Refresh();
}
