#include "as_start_menu.h"
#include "as_game.h"
#include "defs.h"
#include "../include/u-gine.h"

void ASStartMenu::Activate() {
	m_mainFont = ResourceManager::Instance().LoadFont("data/monospaced.png");

	m_menuOptions.Add(new MenuOption(EM_LEVEL_1, new String("Level 1")));
	m_menuOptions.Add(new MenuOption(EM_LEVEL_2, new String("Level 2")));
	m_menuOptions.Add(new MenuOption(EM_LEVEL_3, new String("Level 3")));
	m_menuOptions.Add(new MenuOption(EM_EXIT_APP, new String("Exit Game")));

	m_imgBackground = new Image(MAIN_MENU_BACKGROUND);

	m_activeOption = 0;
	m_elapsedKeyInput = 0;
	m_canInput = false;

	Renderer::Instance().SetBlendMode(Renderer::Instance().ALPHA);		//this allows menu text to be renderer without a solid background
	
	Screen::Instance().SetTitle(String("DODGER"));
}

void ASStartMenu::Deactivate() {
	for (uint8 i = 0; i < m_menuOptions.Size(); i++) {
		delete m_menuOptions[i];
	}

	//more effective way of holding font?
	ResourceManager::Instance().FreeFonts();
}

void ASStartMenu::ProcessInput() {
	if (m_canInput == true) {
		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
			if (m_menuOptions[m_activeOption]->option == EM_LEVEL_1) {
				currentMenuOp = EM_LEVEL_1;
				GSetWantedState(AS_GAME);
			} else if (m_menuOptions[m_activeOption]->option == EM_LEVEL_2) {
				currentMenuOp = EM_LEVEL_2;
				GSetWantedState(AS_GAME);
			} else if (m_menuOptions[m_activeOption]->option == EM_LEVEL_3) {
				currentMenuOp = EM_LEVEL_3;
				GSetWantedState(AS_GAME);
			} else if (m_menuOptions[m_activeOption]->option == EM_EXIT_APP) {
				GSetWantedState(AS_EXIT_APP);
				currentMenuOp = EM_EXIT_APP;
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

	//start game text
	for (uint8 i = 0; i < m_menuOptions.Size(); i++) {
		m_mainFont->SetX(static_cast<float>(Screen::Instance().GetWidth() / 2 - (m_mainFont->GetTextWidth(*m_menuOptions[i]->text) / 2)));
		m_mainFont->SetY(static_cast<float>(MENU_MARGIN + (Screen::Instance().GetHeight() / m_mainFont->GetTextHeight(*m_menuOptions[i]->text) * i)));
		
		if (i == m_activeOption) {
			Renderer::Instance().SetColor(0, 255, 0, 255);
			Renderer::Instance().DrawEllipse(m_mainFont->GetX() - MENU_POINTER_MARGIN, m_mainFont->GetY() + m_mainFont->GetTextHeight(*m_menuOptions[i]->text) / 2, 4, 4);
		} else
			Renderer::Instance().SetColor(0, 0, 255, 255);
		m_mainFont->Render(*m_menuOptions[i]->text, m_mainFont->GetX(), m_mainFont->GetY());
	}

	Screen::Instance().Refresh();
}

void ASStartMenu::RestartKeyElapsed() {
	m_canInput = false;
	m_elapsedKeyInput = 0;
}