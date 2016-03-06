#ifndef _COMPONENT_COLLISION_H
#define _COMPONENT_COLLISION_H

#include "component.h"

class Sprite;

class ComponentCollision: public Component {
public:
	ComponentCollision(Entity * et, Sprite * sprt);

	virtual void ReceiveMessage(Message * const msg);
	virtual void Update(float elapsed);
private:
	Sprite * m_sprite;
};

#endif //!_COMPONENT_COLLISION_H