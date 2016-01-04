#ifndef _GAME_H
#define _GAME_H

#include "../include/u-gine.h"

class Entity;
class UI;
class World;

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