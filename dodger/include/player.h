#ifndef _PLAYER_H
#define _PLAYER_H

#include "defs.h"
#include "entity.h"
#include "../../include/u-gine.h"

class Player: public Entity {
public:
	Player(EDodgerEntityType type);
};

#endif //!_PLAYER_H