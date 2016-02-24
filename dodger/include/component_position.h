#ifndef _COMPONENT_POSITION_H
#define _COMPONENT_POSITION_H

#include "component.h"

class Entity;
class Message;

class ComponentPosition: public Component {
public:
	ComponentPosition(Entity * et, float x, float y);

	virtual void ReceiveMessage(Message * msg);

	virtual void Update();
private:
	float m_x, m_y;
};

#endif //!_COMPONENT_POSITION_H