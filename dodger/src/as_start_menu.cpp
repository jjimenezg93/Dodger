#include "../include/as_game.h"
#include "../include/as_start_menu.h"
#include "../include/defs.h"
#include "../../include/u-gine.h"

ASStartMenu::~ASStartMenu() {
	ResourceManager::Instance().FreeResources();
	for (uint8 i = 0; i < m_menuOptions.Size(); i++) {
		delete m_menuOptions[i];
	}
}

void ASStartMenu::Activate() {
	m_imgBackground = new Image(MAIN_MENU_BACKGROUND);
	m_mainFont = ResourceManager::Instance().LoadFont("data/monospaced.png");

	m_menuOptions.Add(new MenuOption(EDMO_LEVEL_1, String("Level 1")));
	m_menuOptions.Add(new MenuOption(EDMO_LEVEL_2, String("Level 2")));
	m_menuOptions.Add(new MenuOption(EDMO_LEVEL_3, String("Level 3")));
	m_menuOptions.Add(new MenuOption(EDMO_EXIT_APP, String("Exit Game")));

	m_activeOption = 0;
	m_elapsedKeyInput = 0;
	m_canInput = false;

	Renderer::Instance().SetBlendMode(Renderer::Instance().ALPHA);		//menu text without solid background
	
	Screen::Instance().SetTitle(String("DODGER - Start Menu"));
}

void ASStartMenu::Deactivate() {
	Screen::Instance().SetTitle(String(""));
}

void ASStartMenu::ProcessInput() {
	if (m_canInput == true) {
		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
			if (m_menuOptions[m_activeOption]->m_option == EDMO_LEVEL_1) {
				GSetWantedState(EDAS_GAME);
				g_currentMenuOp = EDMO_LEVEL_1;
			} else if (m_menuOptions[m_activeOption]->m_option == EDMO_LEVEL_2) {
				GSetWantedState(EDAS_GAME);
				g_currentMenuOp = EDMO_LEVEL_2;
			} else if (m_menuOptions[m_activeOption]->m_option == EDMO_LEVEL_3) {
				GSetWantedState(EDAS_GAME);
				g_currentMenuOp = EDMO_LEVEL_3;
			} else if (m_menuOptions[m_activeOption]->m_option == EDMO_EXIT_APP) {
				g_currentMenuOp = EDMO_EXIT_APP;
				GSetWantedState(EDAS_EXIT_APP);
			}
			RestartKeyElapsed();
		}
		if (Screen::Instance().KeyPressed(GLFW_KEY_UP) && m_activeOption > 0) {
			m_activeOption--;
			RestartKeyElapsed();
		} else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN) && m_activeOption < m_menuOptions.Size() - 1) {
			m_activeOption++;
			RestartKeyElapsed();
		}
	}
}

void ASStartMenu::Run() {
	if (m_elapsedKeyInput >= MENU_DELAY)
		m_canInput = true;
	m_elapsedKeyInput += Screen::Instance().ElapsedTime();
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
	for (uint8 i = 0; i < m_menuOptions.Size(); i++) {
		m_mainFont->SetX(static_cast<float>(Screen::Instance().GetWidth() / 2 - (m_mainFont->GetTextWidth(*m_menuOptions[i]->m_text) / 2)));
		m_mainFont->SetY(static_cast<float>(MENU_MARGIN + (Screen::Instance().GetHeight() / m_mainFont->GetTextHeight(*m_menuOptions[i]->m_text) * i)));
		
		if (i == m_activeOption) {
			Renderer::Instance().SetColor(0, 255, 0, 255);
			Renderer::Instance().DrawEllipse(m_mainFont->GetX() - MENU_POINTER_MARGIN, m_mainFont->GetY() + m_mainFont->GetTextHeight(*m_menuOptions[i]->m_text) / 2, 4, 4);
		} else
			Renderer::Instance().SetColor(0, 0, 255, 255);
		m_mainFont->Render(*m_menuOptions[i]->m_text, m_mainFont->GetX(), m_mainFont->GetY());
	}

	Screen::Instance().Refresh();
}

void ASStartMenu::RestartKeyElapsed() {
	m_canInput = false;
	m_elapsedKeyInput = 0;
}