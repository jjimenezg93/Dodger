#ifndef AS_MENU_H
#define AS_MENU_H

#include "app_state.h"
#include "defs.h"
#include "../include/u-gine.h"

struct MenuOption {
	MenuOption(EMenuOp op, String *str) { option = op; text = str; }
	~MenuOption() { delete text; }

	EMenuOp option;
	String *text;
};

class ASStartMenu: public AppState {
public:
	virtual void Activate();
	virtual void Deactivate();
	virtual void ProcessInput();
	virtual void Run();
	virtual void Draw();
private:
	Font *m_mainFont;
	Array<MenuOption *> m_menuOptions;
	uint8 m_activeOption;
	Image *m_imgBackground;
};

#endif //!_AS_MENU_H