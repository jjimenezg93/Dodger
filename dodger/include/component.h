#ifndef _COMPONENT_H
#define _COMPONENT_H

class Entity;
class Message;

class Component {
public:
	virtual void ReceiveMessage(Message * msg) = 0;
	virtual void Update() = 0;
protected:	
	Entity * m_owner;
};

#endif //!_COMPONENT_H