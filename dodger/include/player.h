#ifndef _PLAYER_H
#define _PLAYER_H

#include "defs.h"
#include "entity.h"
#include "../../include/u-gine.h"

class Player: public Entity {
public:
	Player(double x, double y, short int dirX, short int dirY);

	//passing elapsed as param makes Player independent from u-gine ElapsedTime
	//void MoveLeft(double elapsed);
	//void MoveRight(double elapsed);
	//void MoveUp(double elapsed);
	//void MoveDown(double elapsed);
};

#endif //!_PLAYER_H