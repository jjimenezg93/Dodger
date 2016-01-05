#ifndef _AS_MENU_H
#define _AS_MENU_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "defs.h"
#include "menu_defs.h"
#include "../../include/u-gine.h"

#pragma warning(disable: 4265)		//destructor not virtual

class ASStartMenu: public AppState {
public:
	virtual void Activate();
	virtual void Deactivate();
	virtual void ProcessInput();
	virtual void Run();
	virtual void Draw();
private:
	void RestartKeyElapsed();

	Font *m_mainFont;
	Array<MenuOption *> m_menuOptions;
	uint8 m_activeOption;
	Image *m_imgBackground;
	double m_elapsedKeyInput;
	bool m_canInput;
};

#pragma warning(default: 4265)

#endif //!_AS_MENU_H