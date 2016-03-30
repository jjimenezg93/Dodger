#ifndef _MENU_DEFS_H
#define _MENU_DEFS_H

#define MENU_FONT_FILENAME "data/monospaced.png"
#define MENU_MARGIN 250
#define MENU_POINTER_MARGIN 32
#define MENU_POINTER_SIZE 4

#include "../../include/string.h"

enum EDodgerMenuOp;

struct MenuOption {
	MenuOption(EDodgerMenuOp op, String str) { m_option = op; m_text = new String(str); }
	~MenuOption() { delete m_text; }

	EDodgerMenuOp m_option;
	String * m_text;
};

#endif //!_MENU_DEFS_H