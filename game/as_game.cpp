#include "as_game.h"
#include "defs.h"

void ASGame::Activate() {
	g_game = new Game();
	g_game->Init();
}

void ASGame::ProcessInput() {
	g_game->ProcessInput();
}

void ASGame::Run() {
	g_game->Run();
}

void ASGame::Draw() {
	g_game->Draw();
}

void ASGame::Deactivate() {
	delete g_game;
}
