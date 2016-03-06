#ifndef _AS_CHOOSE_LANG_H
#define _AS_CHOOSE_LANG_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "defs.h"
#include "menu_defs.h"
#include "../../include/u-gine.h"

class ASChooseLang: public AppState {
public:
	virtual ~ASChooseLang();

	virtual void Activate();
	virtual void Deactivate();
	virtual void ProcessInput();
	virtual void Run();
	virtual void Draw();
private:
	void RestartKeyElapsed();
	void SelectLang(EDodgerMenuOp);

	Image * m_imgBackground;
	Font * m_mainFont;

	Array<MenuOption *> m_menuOptions;
	uint8 m_activeOption;

	double m_elapsedKeyInput;
	bool m_canInput;
};

#endif //!_AS_START_MENU_H