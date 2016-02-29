#ifndef _COMPONENT_POSITION_H
#define _COMPONENT_POSITION_H

#include "component.h"

class Entity;
struct Message;

class ComponentPosition: public Component {
public:
	ComponentPosition(Entity * et, float x, float y);

	virtual void ReceiveMessage(Message * msg);

	virtual void Update(float elapsed);
private:
	float m_x, m_y;
};

#endif //!_COMPONENT_POSITION_H