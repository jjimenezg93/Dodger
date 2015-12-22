#ifndef _DEFS_H
#define _DEFS_H

#include "app_state.h"
#include "game.h"

#define SPACE_BACKGROUND "data/space_bg.jpg"

enum Color { DG_CLR_RED, DG_CLR_GREEN, DG_CLR_BLUE, DG_CLR_YELLOW, DG_CLR_WHITE, DG_CLR_NUM_COLORS };

enum EntityType { ET_PLAYER, ET_POINTS, ET_ENEMY, ET_ADD_SPEED, ET_SUB_SPEED, ET_NUM_COLORS };

extern AppState *g_currentAppState;
extern EAppState g_wantedState;
extern Game *g_game;

extern void GSetWantedState(EAppState newState);

#endif //!_DEFS_H