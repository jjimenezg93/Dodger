#ifndef _WORLD_H
#define _WORLD_H

#include "defs.h"
#include "../include/u-gine.h"

class Entity;

class World {
public:
	World(unsigned short int id, unsigned short int maxEnem, unsigned short int initSpeed);
	~World();

	void Run();
	void Draw();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	unsigned short int GetWorldSpeed() const;

private:
	bool IsCollision(Entity *ra, Entity *rb);
	Entity * RandomSpawnEntity();
	EntityType RandomEntityType();
	void DespawnEntity(int pos);
	void CheckAndUpdateEntityDirection(Entity *object);

	Image *m_imgBackground;
	Array<Entity *> m_entities;
	Entity *m_player;					//makes collision detection easier
	unsigned short int m_id;			//future use?
	unsigned short int m_maxEnemies;
	unsigned short int m_worldSpeed;
};

#endif //!_WORLD_H