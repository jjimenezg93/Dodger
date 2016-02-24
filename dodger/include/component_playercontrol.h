#ifndef _COMPONENT_PLAYERCONTROL_H
#define _COMPONENT_PLAYERCONTROL_H

#include "component.h"

class Entity;
class Message;
class Sprite;

class ComponentPlayerControl: public Component {
public:
	ComponentPlayerControl(Entity * et);

	virtual void ReceiveMessage(Message * msg);

	virtual void Update();
private:
	Sprite * m_sprite;
};

#endif //!_COMPONENT_PLAYERCONTROL_H