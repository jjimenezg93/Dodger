#ifndef _DEFS_H
#define _DEFS_H

class AppState;
class Game;
enum EDodgerAppState;

#define DEFAULT_BACKGROUND "data/space_bg.jpg"
#define MAIN_MENU_BACKGROUND "data/main_menu_bg.jpg"
#define MENU_DELAY 0.2
#define LANG_EN_FILENAME "data/text_en.txt"
#define LANG_ES_FILENAME "data/text_es.txt"
#define LEVEL_1_FILENAME "data/level1.txt"
#define LEVEL_2_FILENAME "data/level2.txt"
#define LEVEL_3_FILENAME "data/level3.txt"

enum EDodgerColor {
	EDG_CLR_BLUE,
	EDG_CLR_GREEN,
	EDG_CLR_RED,
	EDG_CLR_WHITE,
	EDG_CLR_YELLOW,
	EDG_CLR_NUM_COLORS
};

enum EDodgerMenuOp {
	EDMO_EXIT_APP,
	EDMO_GAME_OVER,
	EDMO_LANG_ES,
	EDMO_LANG_EN,
	EDMO_LEVEL_1,
	EDMO_LEVEL_2, 
	EDMO_LEVEL_3,
	EDMO_START_MENU,
	EDMO_NUM_OPTIONS
};
enum EDodgerEntityType {
	EDET_PLAYER,
	EDET_ADD_SPEED,
	EDET_ENEMY,
	EDET_POINTS,
	EDET_SUB_SPEED,
	EDET_NUM_TYPES
};

extern AppState * g_currentAppState;
extern EDodgerAppState g_wantedState;
extern Game * g_game;

extern EDodgerMenuOp g_currentMenuOp;

extern void GSetWantedState(EDodgerAppState newState);

#endif //!_DEFS_H