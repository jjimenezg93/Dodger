#ifndef GAME_H
#define GAME_H

class Rect;
#include "../include/u-gine.h"

class Game {
public:
	void Init();
	void ProcessInput();
	void Run();
	void Draw();

	int GetGameSpeed() { return this->m_speed; }
private:
	bool isCollision(Rect *ra, Rect *rb);
	Rect * randomSpawnObject();
	void despawnObject(int pos);
	void checkAndUpdateObjectDirection(Rect *object);

	String m_windowTitle;
	Rect *m_player;
	int m_points;
	int m_speed;
	int m_randomGen;
	Array<Rect *> m_objects;
};

#endif //!_GAME_H