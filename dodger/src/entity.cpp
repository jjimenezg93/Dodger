#include "../include/entity.h"
#include "../include/world.h"
#include "../include/component.h"
#include "../include/messages.h"

Entity::Entity(const EDodgerEntityType type = EDET_POINTS) {
	m_type = type;
}

Entity::~Entity() {}

void Entity::AddComponent(Component * const comp) {
	m_components.insert(m_components.end(), comp);
}

void Entity::ReceiveMessage(Message * const msg) {
	for (std::vector<Component *>::iterator it = m_components.begin();
			it != m_components.end(); it++) {
		(*it)->ReceiveMessage(msg);
	}
}

void Entity::Update(float elapsed) {
	for (std::vector<Component *>::iterator it = m_components.begin();
			it != m_components.end(); it++) {
		(*it)->Update(elapsed);
	}
}