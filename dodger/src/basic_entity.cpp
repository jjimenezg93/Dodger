#include "../include/basic_entity.h"

BasicEntity::BasicEntity(double x, double y, short int dirX,
		short int dirY, EDodgerEntityType type = EDET_POINTS): Entity(x, y, dirX, dirY, type) {}