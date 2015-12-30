#ifndef _DEFS_H
#define _DEFS_H

#include "app_state.h"
#include "game.h"

#define MAIN_MENU_BACKGROUND "data/main_menu_bg.jpg"
#define DEFAULT_BACKGROUND "data/space_bg.jpg"
#define MENU_DELAY 0.2
#define LEVEL_FILE_PARAMS 3
#define LEVEL_1_FILENAME "data/level1.txt"
#define LEVEL_2_FILENAME "data/level2.txt"
#define LEVEL_3_FILENAME "data/level3.txt"

enum Color { DG_CLR_RED, DG_CLR_GREEN, DG_CLR_BLUE, DG_CLR_YELLOW, DG_CLR_WHITE, DG_CLR_NUM_COLORS };
enum EMenuOp { EM_START_MENU, EM_EXIT_APP, EM_LEVEL_1, EM_LEVEL_2, EM_LEVEL_3, EM_NUM_OPTIONS };
enum EntityType { ET_PLAYER, ET_POINTS, ET_ENEMY, ET_ADD_SPEED, ET_SUB_SPEED, ET_NUM_COLORS };

extern AppState *g_currentAppState;
extern EAppState g_wantedState;
extern Game *g_game;

extern EMenuOp currentMenuOp;

extern void GSetWantedState(EAppState newState);

#endif //!_DEFS_H