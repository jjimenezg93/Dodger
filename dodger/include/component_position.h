#ifndef _COMPONENT_POSITION_H
#define _COMPONENT_POSITION_H

#include "component.h"
#include "entity.h"

//struct UpdatePosMessage: public Message {
//	float x, y;
//};

class ComponentPosition: public Component {
public:
	ComponentPosition(Entity * et, Sprite * sprt);

	virtual void ReceiveMessage(Message * msg);

	virtual void Update();
private:

};

#endif //!_COMPONENT_POSITION_H