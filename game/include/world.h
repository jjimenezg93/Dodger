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

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	int GetWorldSpeed() const;

private:
	bool IsCollision(Entity *ra, Entity *rb);
	Entity * RandomSpawnEntity();
	EntityType RandomEntityType();
	void DespawnEntity(unsigned int pos);
	void CheckAndUpdateEntityDirection(Entity *object);

	Image *m_imgBackground;
	Array<Entity *> m_entities;
	Player *m_player;					//makes collision detection easier
	int m_id;			//future use (e.g. highscores or save game)
	int m_maxCollidables;
	int m_worldSpeed;
};

#endif //!_WORLD_H