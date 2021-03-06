#include "../include/../include/as_game.h"
#include "../include/../include/defs.h"
#include "../include/../include/game.h"

ASGame::~ASGame() {
	delete g_game;
}

void ASGame::Activate() {
	g_game = new Game();
	g_game->Init();
}

void ASGame::Deactivate() {}

void ASGame::ProcessInput() {
	g_game->ProcessInput();
}

void ASGame::Run() {
	g_game->Run();
}

void ASGame::Draw() {
	g_game->Draw();
}
