#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"

#define SPEED 50

float genRandomF(double min, double max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min) + min);
}

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	//IMAGES
	Image * alienImg = ResourceManager::Instance().LoadImage("data/alien.png");
	alienImg->SetMidHandle();

	CollisionPixelData * alienColData = ResourceManager::Instance().LoadCollisionPixelData("data/aliencol.png");

	Map * map = new Map(String("data/map.tmx"));

	MapScene * mainScene = new MapScene(map);

	Sprite * alienSprite = mainScene->CreateSprite(alienImg);
	alienSprite->SetPosition(alienSprite->GetImage()->GetWidth() / 2, alienSprite->GetImage()->GetHeight() / 2);
	alienSprite->SetCollisionPixelData(alienColData);
	alienSprite->SetCollision(Sprite::CollisionMode::COLLISION_PIXEL);
	(mainScene->GetCamera()).SetBounds(0, 0, map->GetWidth(), map->GetHeight());
	(mainScene->GetCamera()).FollowSprite(alienSprite);

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();
		
		if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			alienSprite->MoveTo(Screen::Instance().GetMouseX() + (mainScene->GetCamera()).GetX(), Screen::Instance().GetMouseY() + (mainScene->GetCamera()).GetY(), 200);
		}

		mainScene->Update(Screen::Instance().ElapsedTime());
		mainScene->Render();

		Screen::Instance().Refresh();
	}

	delete mainScene;
	delete map;
	ResourceManager::Instance().FreeResources();

	return 0;
}