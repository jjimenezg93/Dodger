#ifndef _GAME_H
#define _GAME_H

#include "../include/u-gine.h"
//#include "world.h"

class Entity;
class UI;
class World;

//	-Game
//		-UI (usa World) -> input e interfaz sobre el mundo (ptr a World y a UI, para por ejemplo indicar actualización por el input y renderizar la puntuación guardada en Game)
//		-World (usa GfxEngine) -> actualiza el estado del mundo, renderiza el mundo, se comunica con el Game para indicarle puntuaciones, etc
//		-GfxEngine (independiente)

class Game {
public:
	~Game();

	void Init();
	void ProcessInput();
	void Run();
	void Draw();

	World * GetWorld() const;
	int GetWorldSpeed() const;		//necessary for Entity constructor

	int GetPoints() const;
	void AddPoints(int p);
	void SubtractPoints(int p);

	int GetRandomGen() const { return m_randomGen; }

private:
	void SetPoints(int newPoints) { m_points = newPoints; }

	void ReadFile(const String *fileName, Array<String> &paramsArray);
	
	String m_windowTitle;

	int m_points;
	int m_speed;
	int m_randomGen;

	UI *m_ui;
	World *m_world;
};

#endif //!_GAME_H