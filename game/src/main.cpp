#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/as_game.h"
#include "../include/as_start_menu.h"
#include "../include/defs.h"

AppState * g_currentAppState;
EAppState g_wantedState;
Game * g_game;

EMenuOp g_currentMenuOp;

void GSetWantedState(EAppState newState) {
	g_wantedState = newState;
}

//first calls Deactivate(), then destroys it
void DestroyState(AppState *stateToDestroy) {
	stateToDestroy->Deactivate();
	delete stateToDestroy;
}

int main() {
	Screen::Instance().Open(1024, 720, false);

	g_currentMenuOp = EMO_START_MENU;
	GSetWantedState(EAS_START_MENU);

#pragma warning(disable: 4127)
	while (1) {
#pragma warning(default: 4127)
		if (g_wantedState == EAS_EXIT_APP)
			break;
		else if (g_wantedState != EAS_NULL) {
			if (g_currentAppState) {
				DestroyState(g_currentAppState);
			}
			g_currentAppState = newAppState(g_wantedState);
			if (g_currentAppState)
				g_currentAppState->Activate();

			GSetWantedState(EAS_NULL);			//critical for this conditions to work properly
		}

		if (g_currentAppState != nullptr) {
			g_currentAppState->ProcessInput();
			g_currentAppState->Run();
			g_currentAppState->Draw();
		}
	}
}