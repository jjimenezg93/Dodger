#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/as_game.h"
#include "../include/as_start_menu.h"
#include "../include/defs.h"
#include "../include/text_manager.h"

AppState * g_currentAppState;
EDodgerAppState g_wantedState;
Game * g_game;

EDodgerMenuOp g_currentMenuOp;

void GSetWantedState(EDodgerAppState newState) {
	g_wantedState = newState;
}

//first calls Deactivate(), then destroys it
void DestroyState(AppState *stateToDestroy) {
	stateToDestroy->Deactivate();
	delete stateToDestroy;
}

int main() {
	Screen::Instance().Open(1024, 720, false);

	g_currentMenuOp = EDMO_LANG_ES;
	GSetWantedState(EDAS_CHOOSE_LANG);

#pragma warning(disable: 4127)
	while (1) {
#pragma warning(default: 4127)
		if (g_wantedState == EDAS_EXIT_APP) {
			break;
		} else if (g_wantedState != EDAS_NULL) {
			if (g_currentAppState) {
				DestroyState(g_currentAppState);
			}
			g_currentAppState = newAppState(g_wantedState);
			if (g_currentAppState) {
				g_currentAppState->Activate();
			}

			GSetWantedState(EDAS_NULL);			//critical for this conditions to work properly
		}

		if (g_currentAppState != nullptr) {
			g_currentAppState->ProcessInput();
			g_currentAppState->Run();
			g_currentAppState->Draw();
		}
	}
}