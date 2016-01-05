//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/as_game.h"
#include "../include/as_start_menu.h"
#include "../include/defs.h"

AppState *g_currentAppState;
EAppState g_wantedState;
Game *g_game;

EMenuOp currentMenuOp;

void GSetWantedState(EAppState newState) {
	g_wantedState = newState;
}

int main() {
	Screen::Instance().Open(1024, 720, false);

	currentMenuOp = EM_START_MENU;
	GSetWantedState(AS_START_MENU);

#pragma warning(disable: 4127)
	while (1) {
#pragma warning(default: 4127)
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