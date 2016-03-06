#include "../include/as_game.h"
#include "../include/as_choose_lang.h"
#include "../include/defs.h"
#include "../../include/u-gine.h"
#include "../include/text_manager.h"

enum EDodgerLang {
	EDL_EN,
	EDL_ES
};

ASChooseLang::~ASChooseLang() {
	ResourceManager::Instance().FreeResources();
	for (uint8 i = 0; i < m_menuOptions.Size(); i++) {
		delete m_menuOptions[i];
	}
}

void ASChooseLang::Activate() {
	SelectLang(EDMO_LANG_EN); //default english -> needed to show language menu

	m_imgBackground = new Image(MAIN_MENU_BACKGROUND);
	m_mainFont = ResourceManager::Instance().LoadFont("data/monospaced.png");

	m_menuOptions.Add(new MenuOption(EDMO_LANG_EN,
		String(TextManager::Instance().GetString("TEXT_LANG_EN").c_str())));
	m_menuOptions.Add(new MenuOption(EDMO_LANG_ES,
		String(TextManager::Instance().GetString("TEXT_LANG_ES").c_str())));

	m_activeOption = 0;
	m_elapsedKeyInput = 0;
	m_canInput = false;

	//text bg
	Renderer::Instance().SetBlendMode(Renderer::Instance().ALPHA);

	Screen::Instance().SetTitle(
		String(String(TextManager::Instance().GetString("TEXT_MAIN_WINDOW").c_str())));
}

void ASChooseLang::Deactivate() {
	Screen::Instance().SetTitle(String(""));
}

void ASChooseLang::ProcessInput() {
	if (m_canInput == true) {
		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER)) {
			if (m_menuOptions[m_activeOption]->m_option == EDMO_LANG_EN
					|| m_menuOptions[m_activeOption]->m_option == EDMO_LANG_ES) {
				SelectLang(m_menuOptions[m_activeOption]->m_option);
			}
			RestartKeyElapsed();

			GSetWantedState(EDAS_START_MENU);
			g_currentMenuOp = EDMO_START_MENU;
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

void ASChooseLang::Run() {
	if (m_elapsedKeyInput >= MENU_DELAY)
		m_canInput = true;
	m_elapsedKeyInput += Screen::Instance().ElapsedTime();
}

void ASChooseLang::Draw() {
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

void ASChooseLang::RestartKeyElapsed() {
	m_canInput = false;
	m_elapsedKeyInput = 0;
}

void ASChooseLang::SelectLang(EDodgerMenuOp op) {
	switch (op) {
	case EDMO_LANG_EN:
		TextManager::Instance().ReadFile(LANG_EN_FILENAME);
		break;
	case EDMO_LANG_ES:
		TextManager::Instance().ReadFile(LANG_ES_FILENAME);
		break;
	default:
		break;
	}
	
}