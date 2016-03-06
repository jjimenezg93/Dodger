#include "../include/../include/app_state.h"
#include "../include/../include/as_choose_lang.h"
#include "../include/../include/as_game.h"
#include "../include/../include/as_game_over.h"
#include "../include/../include/as_start_menu.h"
#include "../include/../include/defs.h"
#include <typeinfo>

AppState *newAppState(EDodgerAppState wanted) {
	switch (wanted) {
	case EDAS_NULL:
		return nullptr;
		break;
	case EDAS_CHOOSE_LANG:
		return new ASChooseLang();
		break;
	case EDAS_START_MENU:
		return new ASStartMenu();
		break;
	case EDAS_GAME:
		return new ASGame();
		break;
	case EDAS_GAME_OVER:
		return new ASGameOver();
		break;
	case EDAS_EXIT_APP:
		return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
}