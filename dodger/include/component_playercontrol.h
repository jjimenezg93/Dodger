#ifndef _COMPONENT_PLAYERCONTROL_H
#define _COMPONENT_PLAYERCONTROL_H

#include "component.h"

class Entity;
struct Message;

class ComponentPlayerControl: public Component {
public:
	ComponentPlayerControl(Entity * et);

	virtual void ReceiveMessage(Message * msg);

	virtual void Update(float elapsed);
private:
	float m_x, m_y;
	bool m_canMoveLeft, m_canMoveRight, m_canMoveUp, m_canMoveDown;
};

#endif //!_COMPONENT_PLAYERCONTROL_H