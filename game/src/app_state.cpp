#include "../include/../include/app_state.h"
#include "../include/../include/as_game.h"
#include "../include/../include/as_game_over.h"
#include "../include/../include/as_start_menu.h"
#include "../include/../include/defs.h"
#include <typeinfo>

AppState *newAppState(EAppState wanted) {
	switch (wanted) {
	case AS_NULL:
		return nullptr;
		break;
	case AS_START_MENU:
		return new ASStartMenu();
		break;
	case AS_GAME:
		return new ASGame();
		break;
	case AS_GAME_OVER:
		return new ASGameOver();
		break;
	case AS_EXIT_APP:
		return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
}