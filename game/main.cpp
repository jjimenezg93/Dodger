#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "defs.h"
#include "as_menu.h"
#include "as_game.h"

//main loop -> app status (Run(), Draw(), ProcessInput())
AppState *g_currentAppState;
AppState *g_wantedState;
Game *g_game;

int main() {
	Screen::Instance().Open(800, 600, false);

	ASMenu *menu = new ASMenu();
	g_wantedState = menu;

	while (1) {
		if (g_wantedState == nullptr) {
			break;
		} else {
			if (g_wantedState != g_currentAppState) {
				if (g_currentAppState) {
					g_currentAppState->Deactivate();
					delete g_currentAppState;
				}
				g_currentAppState = g_wantedState;
				g_currentAppState->Activate();
			}
		}
		g_currentAppState->ProcessInput();
		g_currentAppState->Run();
		g_currentAppState->Draw();
	}
}