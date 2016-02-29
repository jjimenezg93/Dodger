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
};

#endif //!_COMPONENT_PLAYERCONTROL_H