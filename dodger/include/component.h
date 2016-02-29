#ifndef _COMPONENT_H
#define _COMPONENT_H

class Entity;
struct Message;

class Component {
public:
	virtual ~Component() {}

	virtual void ReceiveMessage(Message * msg) = 0;
	virtual void Update(float elapsed) = 0;
protected:	
	Entity * m_owner;
};

#endif //!_COMPONENT_H