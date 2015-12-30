#ifndef _MENU_OPTION_H
#define _MENU_OPTION_H

#include "defs.h"

#define MENU_MARGIN 250
#define MENU_POINTER_MARGIN 32
#define MENU_POINTER_SIZE 4

struct MenuOption {
	MenuOption(EMenuOp op, String *str) { option = op; text = str; }
	~MenuOption() { delete text; }

	EMenuOp option;
	String *text;
};

#endif //!_MENU_OPTION_H