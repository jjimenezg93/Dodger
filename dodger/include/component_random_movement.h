#ifndef _COMPONENT_RANDOM_MOVEMENT_H
#define _COMPONENT_RANDOM_MOVEMENT_H

#include "component.h"

class ComponentRandomMovement: public Component {
public:
	ComponentRandomMovement(Entity * et, int dirX, int dirY);

	virtual void ReceiveMessage(Message * msg);

	virtual void Update(float elapsed);
private:
	int m_dirX, m_dirY;
	float m_lastChangeX, m_lastChangeY;
};

#endif //!_COMPONENT_RANDOM_MOVEMENT_H