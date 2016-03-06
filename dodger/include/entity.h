#ifndef _ENTITY_H
#define _ENTITY_H

#pragma warning(disable: 4820)

#include "defs.h"

#include <vector>

class Component;
struct Message;

class Entity {
public:
	Entity(const EDodgerEntityType type);
	virtual ~Entity();

	virtual EDodgerEntityType GetType() const { return m_type; }
	virtual void SetType(const EDodgerEntityType newType) { m_type = newType; } //not in use atm

	void AddComponent(Component * const comp);

	void ReceiveMessage(Message * const msg);
	virtual void Update(float elapsed);
private:
	std::vector<Component *> m_components;

	EDodgerEntityType m_type;
};

#endif //!_ENTITY_H