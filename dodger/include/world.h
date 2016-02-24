#ifndef _WORLD_H
#define _WORLD_H

#pragma warning(disable: 4820)

#include "defs.h"
#include "../../include/u-gine.h"

class Entity;
class Player;

class World {
public:
	World(const String background, int id, int maxCollid, int initSpeed);
	~World();

	void Run();
	void Draw();

	Player * GetPlayer() { return m_player; }

	/*void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();*/

	int GetWorldSpeed() const { return m_worldSpeed; }
private:
	bool IsCollision(Entity * ra, Entity * rb);
	Entity * RandomSpawnEntity();
	void DespawnEntity(unsigned int pos);
	EDodgerEntityType RandomGenEntityType();
	void CheckAndUpdateEntityDirection(Entity * object);

	//Image * m_imgBackground;
	Scene * m_scene;
	Array<Entity *> m_entities;
	Player * m_player;			//makes collision detection easier
	int m_id;			//future use (e.g. highscores or save game)
	int m_maxCollidables;
	int m_worldSpeed;
};

#endif //!_WORLD_H