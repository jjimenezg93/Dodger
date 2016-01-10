#ifndef _GAME_H
#define _GAME_H

#include "../../include/u-gine.h"

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

	World * GetWorld() const { return m_world; }
	int GetWorldSpeed() const;					//defined in .cpp in order to avoid dependency in .h

	int GetPoints() const { return m_points; }
	void AddPoints(int p) { m_points += p; }
	void SubtractPoints(int p) { m_points -= p; }

	int GetRandomGen() const { return m_randomGen; }
private:
	void SetPoints(int newPoints) { m_points = newPoints; }

	void ReadFile(const String * fileName, Array<String> &paramsArray);
	
	UI * m_ui;
	World * m_world;
	
	String m_windowTitle;

	int m_points;
	int m_speed;
	int m_randomGen;
};

#endif //!_GAME_H