#ifndef _COMPONENT_RENDER_H
#define _COMPONENT_RENDER_H

#include "component.h"

class Entity;
class Sprite;

class ComponentRender: public Component {
public:
	ComponentRender(Entity * et, Sprite * sprt);

	virtual void ReceiveMessage(Message * msg);

	virtual void Update();
private:
	Sprite * m_sprite;
};

#endif //!_COMPONENT_RENDER_H