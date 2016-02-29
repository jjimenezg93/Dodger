#ifndef _BASIC_ENTITY_H
#define _BASIC_ENTITY_H

#include "entity.h"

class World;

class BasicEntity: public Entity {
public:
	BasicEntity(double x, double y, short int dirX, short int dirY, EDodgerEntityType type);
private:
	
};

#endif //!_BASIC_ENTITY_H