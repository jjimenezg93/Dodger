#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "as_start_menu.h"
#include "as_game.h"
#include "defs.h"

AppState *g_currentAppState;
EAppState g_wantedState;
Game *g_game;

void GSetWantedState(EAppState newState) {
	g_wantedState = newState;
}

int main() {
	Screen::Instance().Open(1024, 720, false);

	GSetWantedState(AS_START_MENU);

	while (1) {
		if (g_wantedState == AS_EXIT_APP)
			break;

		if (g_wantedState != AS_NULL) {
			if (g_currentAppState) {
				g_currentAppState->Deactivate();
				delete g_currentAppState;
			}

			g_currentAppState = newAppState(g_wantedState);
			if (g_currentAppState)
				g_currentAppState->Activate();

			GSetWantedState(AS_NULL);
		}

		if (g_currentAppState != nullptr) {
			g_currentAppState->ProcessInput();
			g_currentAppState->Run();
			g_currentAppState->Draw();
		}
	}
}